#include "main.h"
#include "node.h"

#include <openvdb/openvdb.h>
#include <openvdb/tools/MeshToVolume.h>
#include <openvdb/tools/VolumeToMesh.h> //sdf rebuilding
#include <openvdb/tools/Interpolation.h>
#include <openvdb/tools/Composite.h> //csg operations

#include "scene.h"
#include "SceneSurface.h"

namespace Node{

BaseSurfaceNode1::BaseSurfaceNode1(uint _level, NodeTree *pnt) : BaseSurfaceNode(_level,pnt), BaseNode(_level,pnt){
	pbgrid = openvdb::FloatGrid::create();
	pbgrid->setGridClass(openvdb::GRID_FOG_VOLUME);
}

BaseSurfaceNode1::~BaseSurfaceNode1(){
	//
}

void BaseSurfaceNode1::Clear(){
	//printf("clear() surface %f MB\n",(float)pbgrid->memUsage()/1e6f);
	//default Surface clear()
	pbgrid->clear();
}

openvdb::FloatGrid::Ptr BaseSurfaceNode1::ComputeLevelSet(openvdb::math::Transform::Ptr pgridtr, float ebvc, float ibvc) const{
	openvdb::FloatGrid::Ptr ptgrid = openvdb::tools::meshToSignedDistanceField<openvdb::FloatGrid>(*pgridtr,vl,tl,ql,ebvc,ibvc);
	return ptgrid;
}

BaseSurfaceNode * BaseSurfaceNode::Create(uint level, NodeTree *pnt){
	return new BaseSurfaceNode1(level,pnt);
}

SurfaceInput::SurfaceInput(uint _level, NodeTree *pnt) : BaseSurfaceNode(_level,pnt), BaseSurfaceNode1(_level,pnt), BaseNode(_level,pnt), ISurfaceInput(_level,pnt){
	//DebugPrintf(">> SurfaceInput()\n");
}

SurfaceInput::~SurfaceInput(){
	//
}

void SurfaceInput::Evaluate(const void *pp){
	//DebugPrintf("---Surface::Evaluate()\n");
	InputNodeParams *pd = (InputNodeParams*)pp;
	SceneData::BaseObject *pbob = std::get<INP_OBJECT>(*pd);
	SceneData::Surface *pobj = dynamic_cast<SceneData::Surface*>(pbob);

	//clear possible data from previous evaluation
	vl.clear();
	tl.clear();
	ql.clear();

	if(!pobj){
		DebugPrintf("Warning: Invalid use of SurfaceInput where %s is expected. Input forced to empty.",typeid(pbob).name());
		return;
	}

	vl.reserve(pobj->vl.size());
	for(uint i = 0; i < pobj->vl.size(); ++i){
		openvdb::Vec3s t(pobj->vl[i].x,pobj->vl[i].y,pobj->vl[i].z);
		vl.push_back(t);
	}
	tl.reserve(pobj->tl.size());
	for(uint i = 0; i < pobj->tl.size(); i += 3){
		openvdb::Vec3I t(pobj->tl[i+0],pobj->tl[i+1],pobj->tl[i+2]);
		tl.push_back(t);
	}
}

Node::ISurfaceInput * ISurfaceInput::Create(uint level, NodeTree *pnt){
	return new SurfaceInput(level,pnt);
}

SolidInput::SolidInput(uint _level, NodeTree *pnt, char _geomch) : BaseSurfaceNode(_level,pnt), BaseSurfaceNode1(_level,pnt), BaseNode(_level,pnt), ISolidInput(_level,pnt), geomch(_geomch){
	//
}

SolidInput::~SolidInput(){
	//
}

void SolidInput::Evaluate(const void *pp){
	InputNodeParams *pd = (InputNodeParams*)pp;

	BaseValueNode<dfloat3> *pnposw = dynamic_cast<BaseValueNode<dfloat3>*>(pnodes[INPUT_POSW]);
	BaseValueNode<dfloat3> *pnscale = dynamic_cast<BaseValueNode<dfloat3>*>(pnodes[INPUT_SCALE]);

	dfloat3 zr(0.0f);
	ValueNodeParams np(&zr,&zr,0.0f,0.0f,&zr,0.0,0.0f,pd);
	pntree->EvaluateNodes0(&np,level+1,emask);

	vl.clear();
	tl.clear();
	ql.clear();

	if(geomch == 'C'){
		vl.reserve(8);
		vl.push_back(openvdb::Vec3s(-1.0f,-1.0f,-1.0f));
		vl.push_back(openvdb::Vec3s(+1.0f,-1.0f,-1.0f));
		vl.push_back(openvdb::Vec3s(+1.0f,-1.0f,+1.0f));
		vl.push_back(openvdb::Vec3s(-1.0f,-1.0f,+1.0f));
		vl.push_back(openvdb::Vec3s(-1.0f,+1.0f,-1.0f));
		vl.push_back(openvdb::Vec3s(+1.0f,+1.0f,-1.0f));
		vl.push_back(openvdb::Vec3s(+1.0f,+1.0f,+1.0f));
		vl.push_back(openvdb::Vec3s(-1.0f,+1.0f,+1.0f));

		ql.reserve(6);
		ql.push_back(openvdb::Vec4I(1,0,4,5));
		ql.push_back(openvdb::Vec4I(2,1,5,6));
		ql.push_back(openvdb::Vec4I(3,2,6,7));
		ql.push_back(openvdb::Vec4I(0,3,7,4));
		ql.push_back(openvdb::Vec4I(2,3,0,1));
		ql.push_back(openvdb::Vec4I(5,4,7,6));
	}

	dfloat3 posw = pnposw->locr(indices[INPUT_POSW]);
	dfloat3 scale = pnscale->locr(indices[INPUT_SCALE]);
	openvdb::Vec3s p(posw.x,posw.y,posw.z);
	openvdb::Vec3s s(scale.x,scale.y,scale.z);
	for(uint i = 0, n = vl.size(); i < n; ++i){
		vl[i] *= s;
		vl[i] += p;
	}
}

Node::ISolidInput * ISolidInput::Create(uint level, NodeTree *pnt, char geomch){
	return new SolidInput(level,pnt,geomch);
}

Displacement::Displacement(uint _level, NodeTree *pnt, float _resf) : BaseSurfaceNode(_level,pnt), BaseSurfaceNode1(_level,pnt), BaseNode(_level,pnt), IDisplacement(_level,pnt), resf(_resf){
	//
	//DebugPrintf(">> Displacement()\n");
}

Displacement::~Displacement(){
	//
}

void Displacement::Evaluate(const void *pp){
	InputNodeParams *pd = (InputNodeParams*)pp;
	const float bvc = 4.0f;

	BaseValueNode<float> *pnoisen = dynamic_cast<BaseValueNode<float>*>(pnodes[INPUT_DISTANCE]);
	BaseValueNode<float> *pmaxn = dynamic_cast<BaseValueNode<float>*>(pnodes[INPUT_MAXIMUM]);
	BaseValueNode<float> *pbilln = dynamic_cast<BaseValueNode<float>*>(pnodes[INPUT_BILLOW]);
	BaseSurfaceNode1 *pnode = dynamic_cast<BaseSurfaceNode1*>(pnodes[INPUT_SURFACE]);

	dfloat3 zr(0.0f);
	ValueNodeParams np(&zr,&zr,0.0f,0.0f,&zr,0.0,0.0f,pd);
	pntree->EvaluateNodes0(&np,level+1,emask);
	float amp = pmaxn->locr(indices[INPUT_MAXIMUM]);

	openvdb::math::Transform::Ptr pgridtr = std::get<INP_TRANSFORM>(*pd);//openvdb::math::Transform::createLinearTransform(s);
	if(resf < 1.0f){
		pgridtr = pgridtr->copy();
		pgridtr->preScale(1.0f/resf);
	}
	pbgrid->setTransform(pgridtr);

	float nvc = ceilf(amp/pgridtr->voxelSize().x()+bvc);
	openvdb::FloatGrid::Ptr psgrid = pnode->ComputeLevelSet(pgridtr,nvc,bvc);

	DebugPrintf("Disp. narrow band = %f+%f (%u voxels)\n",amp,pgridtr->voxelSize().x()*bvc,(uint)nvc);
	DebugPrintf("> Displacing SDF...\n");

	typedef std::tuple<openvdb::FloatGrid::Ptr, openvdb::FloatGrid::Accessor, openvdb::FloatGrid::ConstAccessor> FloatGridT;
	tbb::enumerable_thread_specific<FloatGridT> tgrida([&]()->FloatGridT{
		openvdb::FloatGrid::Ptr ptgrid = openvdb::FloatGrid::create();
		ptgrid->setTransform(pgridtr);
		ptgrid->setGridClass(openvdb::GRID_FOG_VOLUME);
		return FloatGridT(ptgrid,ptgrid->getAccessor(),psgrid->getConstAccessor());
	});
	openvdb::math::CPT_RANGE<openvdb::math::UniformScaleMap,openvdb::math::CD_2ND> cptr;
	tbb::parallel_for(openvdb::tree::IteratorRange<openvdb::FloatGrid::ValueOnIter>(psgrid->beginValueOn()),[&](openvdb::tree::IteratorRange<openvdb::FloatGrid::ValueOnIter> &r){
		FloatGridT &fgt = tgrida.local();
		for(; r; ++r){ //++fi
			const openvdb::FloatGrid::ValueOnIter &m = r.iterator();

			openvdb::Coord c = m.getCoord();
			openvdb::Vec3s posw = pgridtr->indexToWorld(c.asVec3d());
			openvdb::Vec3s cptw = cptr.result(*pgridtr->map<openvdb::math::UniformScaleMap>(),std::get<2>(fgt),c);

			ValueNodeParams np1((dfloat3*)posw.asPointer(),(dfloat3*)cptw.asPointer(),m.getValue(),0.0f,(dfloat3*)posw.asPointer(),0.0f,0.0f,pd);
			pntree->EvaluateNodes0(&np1,level+1,emask);

			float f = fabs(pnoisen->locr(indices[INPUT_DISTANCE]));
			std::get<1>(fgt).setValue(c,f); //set only the displacement, so that billowing can be done
		}
	});

	//This could probably be faster with parallel reduction
	openvdb::FloatGrid::Accessor sgrida = psgrid->getAccessor();
	openvdb::FloatGrid::Accessor bgrida = pbgrid->getAccessor();
	FloatGridBoxSampler bsampler(*pnode->pbgrid); //TODO: may use the cached version for the single threaded portion below
	for(tbb::enumerable_thread_specific<FloatGridT>::const_iterator q = tgrida.begin(); q != tgrida.end(); ++q){
		//
		for(openvdb::FloatGrid::ValueOnIter m = std::get<0>(*q)->beginValueOn(); m.test(); ++m){
			openvdb::Coord c = m.getCoord();

			float d = sgrida.getValue(c);
			float f = m.getValue();

			float b = pbilln->locr(indices[INPUT_BILLOW]);
			if(b > 0.0f){
				openvdb::math::Vec3s posw = pgridtr->indexToWorld(c);
				b = powf(std::min(bsampler.wsSample(posw),1.0f),b);
				f *= b;
			}

			bgrida.setValue(c,f/amp);
			sgrida.setValue(c,d-f);

			//if(omask & (1<<OUTPUT_GRID))
				//bgrida.setValue(c,d/amp);
		}
	}

	DebugPrintf("> Rebuilding...\n");

	openvdb::tools::volumeToMesh<openvdb::FloatGrid>(*psgrid,vl,tl,ql,0.0);
}

Node::IDisplacement * IDisplacement::Create(uint level, NodeTree *pnt, float resf){
	return new Displacement(level,pnt,resf);
}

Transform::Transform(uint _level, NodeTree *pnt) : BaseSurfaceNode(_level,pnt), BaseSurfaceNode1(_level,pnt), BaseNode(_level,pnt), ITransform(_level,pnt){
	//
}

Transform::~Transform(){
	//
}

void Transform::Evaluate(const void *pp){
	//TODO: transform the vertices
}

Node::ITransform * ITransform::Create(uint level, NodeTree *pnt){
	return new Transform(level,pnt);
}

CSG::CSG(uint _level, NodeTree *pnt, float _opch) : BaseSurfaceNode(_level,pnt), BaseSurfaceNode1(_level,pnt), BaseNode(_level,pnt), ICSG(_level,pnt), opch(_opch){
	//
}

CSG::~CSG(){
	//
}

void CSG::Evaluate(const void *pp){
	InputNodeParams *pd = (InputNodeParams*)pp;
	const float bvc = 4.0f;

	BaseSurfaceNode1 *pnode1 = dynamic_cast<BaseSurfaceNode1*>(pnodes[INPUT_SURFACEA]);
	BaseSurfaceNode1 *pnode2 = dynamic_cast<BaseSurfaceNode1*>(pnodes[INPUT_SURFACEB]);

	DebugPrintf("> CSG|%c operating surface...\n",opch);

	openvdb::math::Transform::Ptr pgridtr = std::get<INP_TRANSFORM>(*pd);
	openvdb::FloatGrid::Ptr pgrid1 = pnode1->ComputeLevelSet(pgridtr,bvc,bvc);
	openvdb::FloatGrid::Ptr pgrid2 = pnode2->ComputeLevelSet(pgridtr,bvc,bvc);

	switch(opch){
	case 'D':
		openvdb::tools::csgDifference(*pgrid1,*pgrid2);
		break;
	case 'I':
		openvdb::tools::csgIntersection(*pgrid1,*pgrid2);
		break;
	case 'U':
		openvdb::tools::csgUnion(*pgrid1,*pgrid2);
		break;
	}

	DebugPrintf("> Rebuilding...\n");

	openvdb::tools::volumeToMesh<openvdb::FloatGrid>(*pgrid1,vl,tl,ql,0.0);
}

Node::ICSG * ICSG::Create(uint level, NodeTree *pnt, char opch){
	return new CSG(level,pnt,opch);
}

}
