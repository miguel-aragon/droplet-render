#ifndef SMMATH_INL
#define SMMATH_INL

#define BLCLOUD_VSIZE 4 //SSE4
#define BLCLOUD_VX 2
#define BLCLOUD_VY 2

#define FL_PERMUTE(v,c) _mm_shuffle_ps(v,v,c)
#define IL_PERMUTE(v,c) _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(v),_mm_castsi128_ps(v),c))//_mm_shuffle_epi32(v,c)

class dfloatN{
public:
	dfloatN(){}
	dfloatN(const class sfloat1 &s);
	dfloatN(float s){
		for(uint i = 0; i < BLCLOUD_VSIZE; v[i++] = s);
	}
	dfloatN(float *p){
		//memcpy(v,p,sizeof(v));
		for(uint i = 0; i < BLCLOUD_VSIZE; v[i] = p[i], ++i);
	}

	float v[BLCLOUD_VSIZE];
} __attribute__((aligned(16)));

class dfloat3{
public:
    dfloat3(){}
    dfloat3(const class float4 &s);
    dfloat3(float s) : x(s), y(s), z(s){}
    dfloat3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}

    inline dfloat3 operator*(float r) const{
        return dfloat3(r*x,r*y,r*z);
    }

	inline dfloat3 operator/(float r) const{
		return dfloat3(x/r,y/r,z/r);
	}

    float x, y, z;
} __attribute__((aligned(16)));

inline dfloat3 operator*(float r, const dfloat3 &s){
    return s*r;
}

inline dfloat3 operator/(float r, const dfloat3 &s){
	return dfloat3(r/s.x,r/s.y,r/s.z);
}

class dfloat4{
public:
    dfloat4(){}
    dfloat4(const class float4 &s);
    dfloat4(float s) : x(s), y(s), z(s), w(s){}
    dfloat4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w){}

	inline dfloat4 operator*(float r) const{
		return dfloat4(r*x,r*y,r*z,r*w);
	}

	inline dfloat4 operator/(float r) const{
		return dfloat4(x/r,y/r,z/r,w/r);
	}

    float x, y, z, w;
} __attribute__((aligned(16)));

inline dfloat4 operator*(float r, const dfloat4 &s){
	return s*r;
}

inline dfloat4 operator/(float r, const dfloat4 &s){
	return dfloat4(r/s.x,r/s.y,r/s.z,r/s.w);
}

class dmatrix44{
public:
    dmatrix44(){}
    //float r[16];
    dfloat4 r[4];
} __attribute__((aligned(16)));

class dintN{
public:
	dintN(){}
	dintN(const class sint1 &s);
	dintN(int s){
		for(uint i = 0; i < BLCLOUD_VSIZE; v[i++] = s);
	}
	dintN(int *p){
		//memcpy(v,p,sizeof(v));
		for(uint i = 0; i < BLCLOUD_VSIZE; v[i] = p[i], ++i);
	}

	int v[BLCLOUD_VSIZE];
} __attribute__((aligned(16)));

class dint3{
public:
    dint3(){}
    //dint3(const class sint4 &);
    dint3(int _x, int _y, int _z) : x(_x), y(_y), z(_z){}
    int x, y, z;
} __attribute__((aligned(16)));

class dint4{
public:
    dint4(){}
    //dint4(const class sint4 &);
    dint4(int _x, int _y, int _z, int _w) : x(_x), y(_y), z(_z), w(_w){}
    int x, y, z, w;
} __attribute__((aligned(16)));

class duintN{
public:
	duintN(){}
	duintN(uint s){
		for(uint i = 0; i < BLCLOUD_VSIZE; v[i++] = s);
	}
	duintN(uint *p){
		//memcpy(v,p,sizeof(v));
		for(uint i = 0; i < BLCLOUD_VSIZE; v[i] = p[i], ++i);
	}

	uint v[BLCLOUD_VSIZE];
} __attribute__((aligned(16)));

class duint3{
public:
    duint3(){}
    duint3(uint _x, uint _y, uint _z) : x(_x), y(_y), z(_z){}
    uint x, y, z;
} __attribute__((aligned(16)));

class duint4{
public:
    duint4(){}
    duint4(uint _x, uint _y, uint _z, uint _w) : x(_x), y(_y), z(_z), w(_w){}
    uint x, y, z, w;
} __attribute__((aligned(16)));

class sfloat1;
class sfloat4;
class sint1;
class sint4;

class sfloat1{
public:
    sfloat1(){
        //
    }

    sfloat1(float a){
        v = _mm_set1_ps(a);
    }

    sfloat1(float x, float y, float z, float w){
        v = _mm_set_ps(w,z,y,x);
    }

    sfloat1(const __m128 &_v){
        v = _v;
    }

    ~sfloat1(){
        //
    }

    sfloat1(const sint1 &s);

    inline operator __m128() const{
        return v;
    }

    inline sfloat1 operator+(const sfloat1 &s) const{
        return _mm_add_ps(v,s.v);
    }

    inline void operator+=(const sfloat1 &s){
        v = _mm_add_ps(v,s.v);
    }

    inline sfloat1 operator-() const{
        return _mm_sub_ps(_mm_setzero_ps(),v);
    }

    inline sfloat1 operator-(const sfloat1 &s) const{
        return _mm_sub_ps(v,s.v);
    }

    inline void operator-=(const sfloat1 &s){
        v = _mm_sub_ps(v,s.v);
    }

    inline sfloat1 operator*(const sfloat1 &s) const{
        return _mm_mul_ps(v,s.v);
    }

    inline void operator*=(const sfloat1 &s){
        v = _mm_mul_ps(v,s.v);
    }

    inline sfloat1 operator/(const sfloat1 &s) const{
        return _mm_div_ps(v,s.v);
    }

    inline void operator/=(const sfloat1 &s){
        v = _mm_div_ps(v,s.v);
    }

    inline sfloat1 operator+(float s) const{
        return _mm_add_ps(v,_mm_set1_ps(s));
    }

    inline sfloat1 operator-(float s) const{
        return _mm_sub_ps(v,_mm_set1_ps(s));
    }

    inline sfloat1 operator*(float s) const{
        return _mm_mul_ps(v,_mm_set1_ps(s));
    }

    inline sfloat1 operator/(float s) const{
        return _mm_div_ps(v,_mm_set1_ps(s));
    }

    template<uint x>
    inline float get() const{
        __m128 t = FL_PERMUTE(v,_MM_SHUFFLE(x,x,x,x));
        return _mm_cvtss_f32(t);
    }

    /*template<>
    inline float get<0>() const{
        return _mm_cvtss_f32(v);
    }*/

    template<uint x>
    inline void set(float f){
        /*const duint4 st[] = {
            duint4(0,0,0,0),
            duint4(3,2,0,1),
            duint4(3,0,1,2),
            duint4(0,2,1,3)
        };
        __m128 r = FL_PERMUTE(v,_MM_SHUFFLE(st[x].x,st[x].y,st[x].z,st[x].w));
        __m128 t = _mm_set_ss(f);
        r = _mm_move_ss(r,t);
        v = FL_PERMUTE(r,_MM_SHUFFLE(st[x].x,st[x].y,st[x].z,st[x].w));*/
        //assert(x == 3);
        if(x == 3){
            __m128 r = FL_PERMUTE(v,_MM_SHUFFLE(0,2,1,3));
            __m128 t = _mm_set_ss(f);
            r = _mm_move_ss(r,t);
            v = FL_PERMUTE(r,_MM_SHUFFLE(0,2,1,3));
        }
    }

    template<uint x>
    inline sfloat1 splat() const{
        return FL_PERMUTE(v,_MM_SHUFFLE(x,x,x,x));
    }

    inline sfloat1 splat(uint x) const{
        return swizzle(x,x,x,x);
    }

    template<uint a, uint b, uint c, uint d>
    inline sfloat1 swizzle() const{
        return FL_PERMUTE(v,_MM_SHUFFLE(d,c,b,a));
    }

    inline sfloat1 swizzle(uint a, uint b, uint c, uint d) const{
        sfloat1 r;
        const uint *psrc = (const uint*)(&v);
        uint *pdst = (uint*)(&r.v);
        pdst[0] = psrc[a];
        pdst[1] = psrc[b];
        pdst[2] = psrc[c];
        pdst[3] = psrc[d];
        return r;
    }

    //------------------------------------------------------------------------------
    //Arithmetic operations and dual input functions are defined as static members

    static inline sfloat1 zero(){
        return _mm_setzero_ps();
    }

    static inline sfloat1 one(){
        return _mm_set1_ps(1.0f);
    }

    static inline sfloat1 trueI(){ //TODO: sint1 class for this
        __m128i t = _mm_set1_epi32(-1);
        return _mm_castsi128_ps(t);
    }

    static inline sfloat1 falseI(){
        return zero();
    }

    static inline sfloat1 selectctrl(uint a, uint b, uint c, uint d){
        __m128i t = _mm_set_epi32(d,c,b,a);
        //t = _mm_cmpgt_epi32(t,_mm_set_epi32(0,0,0,0));
        t = _mm_cmpgt_epi32(t,_mm_setzero_si128());
        return _mm_castsi128_ps(t);
    }

    static inline sfloat1 select(const sfloat1 &a, const sfloat1 &b, const sfloat1 &c){
        __m128 t1 = _mm_andnot_ps(c.v,a.v);
        __m128 t2 = _mm_and_ps(c.v,b.v);
        return _mm_or_ps(t1,t2);
    }

    static inline sfloat1 min(const sfloat1 &a, const sfloat1 &b){
        return _mm_min_ps(a.v,b.v);
    }

    static inline sfloat1 max(const sfloat1 &a, const sfloat1 &b){
        return _mm_max_ps(a.v,b.v);
    }

    static inline sfloat1 saturate(const sfloat1 &s){
        return _mm_max_ps(_mm_min_ps(s.v,_mm_set1_ps(1.0f)),_mm_set1_ps(-1.0f));
    }

    static inline sfloat1 floor(const sfloat1 &s){
#ifdef USE_SSE4
        return _mm_floor_ps(s.v);
#else
        /*__m128i t = _mm_and_si128(_mm_castps_si128(s.v),_mm_set1_epi32(0x7FFFFFFF));
        t = _mm_cmplt_epi32(t,_mm_set1_epi32(8388608));
        //
        __m128i i = _mm_cvttps_epi32(s.v);
        r.v = _mm_cvtepi32_ps(i);
        __m128 l = _mm_cmpgt_ps(r.v,s.v);
        //
        l = _mm_cvtepi32_ps(_mm_castps_si128(l));
        r.v = _mm_add_ps(r.v,l);
        //
        r.v = _mm_or_ps(_mm_and_ps(r.v,_mm_castsi128_ps(t)),_mm_castsi128_ps(_mm_andnot_si128(t,_mm_castps_si128(s.v))));*/
        sfloat1 r;
        __attribute__((aligned(16))) float a[4];
        _mm_store_ps(a,s.v);
        r.v = _mm_setr_ps(
            floorf(a[0]),
            floorf(a[1]),
            floorf(a[2]),
            floorf(a[3]));
        return r;
#endif
    }

    static inline sfloat1 ceil(const sfloat1 &s){
#ifdef USE_SSE4
        return _mm_ceil_ps(s.v);
#else
        /*__m128i t = _mm_and_si128(_mm_castps_si128(s.v),_mm_set1_epi32(0x7FFFFFFF));
        t = _mm_cmplt_epi32(t,_mm_set1_epi32(8388608));
        //
        __m128i i = _mm_cvttps_epi32(s.v);
        r.v = _mm_cvtepi32_ps(i);
        __m128 l = _mm_cmplt_ps(r.v,s.v);
        //
        l = _mm_cvtepi32_ps(_mm_castps_si128(l));
        r.v = _mm_sub_ps(r.v,l);
        //
        r.v = _mm_or_ps(_mm_and_ps(r.v,_mm_castsi128_ps(t)),_mm_castsi128_ps(_mm_andnot_si128(t,_mm_castps_si128(s.v))));*/
        sfloat1 r;
        __attribute__((aligned(16))) float a[4];
        _mm_store_ps(a,s.v);
        r.v = _mm_setr_ps(
            ceilf(a[0]),
            ceilf(a[1]),
            ceilf(a[2]),
            ceilf(a[3]));
        return r;
#endif
    }

    static inline sfloat1 lerp(const sfloat1 &a, const sfloat1 &b, const sfloat1 &t){
        return a*(sfloat1::one()-t)+b*t;
    }

    static inline sfloat1 sqrt(const sfloat1 &s){
        return _mm_sqrt_ps(s.v);
    }

    static inline sfloat1 pow(const sfloat1 &s, const sfloat1 &p){
        //TODO: remove this unvectorized scourge, use minimax for known ranges and constant exponents
        /*dfloat4 a, b;
        float4::store(&a,s);
        float4::store(&b,p);
        sfloat1 r = sfloat1(
            powf(a.x,b.x),
            powf(a.y,b.y),
            powf(a.z,b.z),
            powf(a.w,b.w));*/
        __attribute__((aligned(16))) float a[4];
        __attribute__((aligned(16))) float b[4];
        _mm_store_ps(a,s.v);
        _mm_store_ps(b,p.v);
        sfloat1 r = sfloat1(
            powf(a[0],b[0]),
            powf(a[1],b[1]),
            powf(a[2],b[2]),
            powf(a[3],b[3]));
        return r;
    }

    static inline sfloat1 abs(const sfloat1 &s){
        sfloat1 r;
        r.v = _mm_setzero_ps();
        r.v = _mm_sub_ps(r.v,s.v);
        r.v = _mm_max_ps(r.v,s.v);
        return r;
    }

    /*static inline sfloat1 acos(const sfloat1 &s){
        __attribute__((aligned(16))) float a[4];
        //dfloat4 a;
        _mm_store_ps(a,s.v);
        sfloat1 r = sfloat1(
            acosf(a[0]),
            acosf(a[1]),
            acosf(a[2]),
            acosf(a[3]));
        return r;
    }

    static inline sfloat1 atan2(const sfloat1 &y, const sfloat1 &x){
        __attribute__((aligned(16))) float a[4];
        __attribute__((aligned(16))) float b[4];
        _mm_store_ps(a,y.v);
        _mm_store_ps(b,x.v);
        sfloat1 r = sfloat1(
            atan2f(a[0],b[0]),
            atan2f(a[1],b[1]),
            atan2f(a[2],b[2]),
            atan2f(a[3],b[3]));
        return r;
    }*/

    static inline sfloat1 Greater(const sfloat1 &a, const sfloat1 &b){
        return _mm_cmpgt_ps(a.v,b.v);
    }

    static inline sfloat1 GreaterOrEqual(const sfloat1 &a, const sfloat1 &b){
        return _mm_cmpge_ps(a.v,b.v);
    }

    static inline sfloat1 Less(const sfloat1 &a, const sfloat1 &b){
        return _mm_cmplt_ps(a.v,b.v);
    }

    static inline sfloat1 LessOrEqual(const sfloat1 &a, const sfloat1 &b){
        return _mm_cmple_ps(a.v,b.v);
    }

    /*
    __m128i vTemp = _mm_cmpeq_epi32(_mm_castps_si128(V1),_mm_castps_si128(V2));
    return ((_mm_movemask_ps(_mm_castsi128_ps(vTemp))==0xf) != 0);*/
    /*static inline int EqualR(const sfloat1 &a, const sfloat1 &b){
        __m128i v =_mm_cmpeq_epi32(_mm_castps_si128(a.v),_mm_castps_si128(b.v));
        return _mm_movemask_ps(_mm_castsi128_ps(v));
    }

    static inline bool AllTrue(int m){
        //return (((CR) & XM_CRMASK_CR6TRUE) == XM_CRMASK_CR6TRUE);
        return (m == 0xf);//(m & 0xf) == 0xf;
    }

    static inline bool AnyTrue(int m){
        //return (((CR) & XM_CRMASK_CR6FALSE) != XM_CRMASK_CR6FALSE);
        return (m != 0);
    }

    static inline bool AnyFalse(int m){
        //return (((CR) & XM_CRMASK_CR6TRUE) != XM_CRMASK_CR6TRUE);
        return (m != 0xf);
    }*/
    static inline uint EqualR(const sfloat1 &a, const sfloat1 &b){
        __m128i v =_mm_cmpeq_epi32(_mm_castps_si128(a.v),_mm_castps_si128(b.v));
        int t = _mm_movemask_ps(_mm_castsi128_ps(v));
        return (t == 0xf?0x00000080:0x00000020);
    }

    static inline bool AllTrue(uint m){
        //return (((CR) & XM_CRMASK_CR6TRUE) == XM_CRMASK_CR6TRUE);
        return ((m & 0x00000080) == 0x00000080);
    }

    static inline bool AnyTrue(uint m){
        //return (((CR) & XM_CRMASK_CR6FALSE) != XM_CRMASK_CR6FALSE);
        return ((m & 0x00000020) != 0x00000020);
    }

    static inline bool AnyFalse(uint m){
        //return (((CR) & XM_CRMASK_CR6TRUE) != XM_CRMASK_CR6TRUE);
        return ((m & 0x00000080) != 0x00000080);
    }

    static inline sfloat1 And(const sfloat1 &a, const sfloat1 &b){
        return _mm_and_ps(a.v,b.v);
    }

    static inline sfloat1 AndNot(const sfloat1 &a, const sfloat1 &b){
        return _mm_andnot_ps(a.v,b.v);
    }

    static inline sfloat1 Or(const sfloat1 &a, const sfloat1 &b){
        return _mm_or_ps(a.v,b.v);
    }

    static inline void store(float *pdst, const sfloat1 &s){
        _mm_store_ps(pdst,s.v);
    }

    static inline sfloat1 load(const float *psrc){
        return _mm_load_ps(psrc);
    }

	static inline void store(dfloatN *pdst, const sfloat1 &s){
		_mm_store_ps(pdst->v,s.v);
	}

	static inline sfloat1 load(const dfloatN *psrc){
		return _mm_load_ps(psrc->v);
	}

    __m128 v;
};

//TODO: typedef __m128 to something, and use above operators -> sfloat1(a)/b
inline __m128 operator*(const __m128 &a, const sfloat1 &b){
    return _mm_mul_ps(a,b.v);
}

inline __m128 operator/(const __m128 &a, const sfloat1 &b){
    return _mm_div_ps(a,b.v);
}

inline sfloat1 operator+(float a, const sfloat1 &b){
    return _mm_add_ps(_mm_set1_ps(a),b.v);
}

inline sfloat1 operator-(float a, const sfloat1 &b){
    return _mm_sub_ps(_mm_set1_ps(a),b.v);
}

inline sfloat1 operator*(float a, const sfloat1 &b){
    return _mm_mul_ps(_mm_set1_ps(a),b.v);
}

inline sfloat1 operator/(float a, const sfloat1 &b){
    return _mm_div_ps(_mm_set1_ps(a),b.v);
}

inline dfloatN::dfloatN(const sfloat1 &s){
	sfloat1::store(v,s);
}

//typedef sfloat1 float4;
class float4 : public sfloat1{
public:
    float4(){}
    float4(__m128 _v){
        v = _v;
    }

    float4(float x, float y, float z, float w){
        v = _mm_set_ps(w,z,y,x);
    }

    float4(sfloat1 _v){
        v = _v.v;
    }

    static inline float4 dot3(const float4 &a, const float4 &b){
#ifdef USE_SSE4
        return _mm_dp_ps(a.v,b.v,0x7f);
#else
        __m128 t = _mm_mul_ps(a.v,b.v);
        t = _mm_and_ps(t,_mm_castsi128_ps(_mm_set_epi32(0,-1,-1,-1)));
        t = _mm_hadd_ps(t,t);
        return _mm_hadd_ps(t,t);
#endif
    }

    static inline float4 dot4(const float4 &a, const float4 &b){
#ifdef USE_SSE4
        return _mm_dp_ps(a.v,b.v,0x7f);
#else
        __m128 t = _mm_mul_ps(a.v,b.v);
        t = _mm_hadd_ps(t,t);
        return _mm_hadd_ps(t,t);
#endif
    }

    static inline float4 cross(const float4 &a, const float4 &b){
        float4 r;
        __m128 t1 = FL_PERMUTE(a.v,_MM_SHUFFLE(3,0,2,1));
        __m128 t2 = FL_PERMUTE(b.v,_MM_SHUFFLE(3,1,0,2));
        r.v = _mm_mul_ps(t1,t2);
        t1 = FL_PERMUTE(t1,_MM_SHUFFLE(3,0,2,1));
        t2 = FL_PERMUTE(t2,_MM_SHUFFLE(3,1,0,2));
        t1 = _mm_mul_ps(t1,t2);
        r.v = _mm_sub_ps(r.v,t1);
        r.v = _mm_and_ps(r.v,_mm_castsi128_ps(_mm_set_epi32(0,-1,-1,-1)));
        return r;
    }

    static inline float4 permute(const float4 &a, const float4 &b, uint x, uint y, uint z, uint w){
        const uint *psrc[] = {(const uint*)&a.v,(const uint*)&b.v};
        float4 r;
        uint *pdst = (uint*)&r.v;
        uint i0 = x&3;
        uint v0 = x>>2;
        pdst[0] = psrc[v0][i0];

        uint i1 = y&3;
        uint v1 = y>>2;
        pdst[1] = psrc[v1][i1];

        uint i2 = z&3;
        uint v2 = z>>2;
        pdst[2] = psrc[v2][i2];

        uint i3 = w&3;
        uint v3 = w>>2;
        pdst[3] = psrc[v3][i3];

        return r;
    }

    static inline void store(float *p, const float4 &s){
        _mm_store_ps(p,s.v);
    }

    static inline void store(dfloat3 *p, const float4 &s){
        __m128 t = FL_PERMUTE(s.v,_MM_SHUFFLE(2,2,2,2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(p),_mm_castps_si128(s.v));
        _mm_store_ss(&p->z,t);
    }

    static inline void store(dfloat4 *p, const float4 &s){
        _mm_store_ps(&p->x,s.v);
    }

    static inline float4 load(const float *p){
        return _mm_load_ps(p);
    }

    static inline float4 load(const dfloat3 *p){
        dfloat4 t(p->x,p->y,p->z,0.0f);
        return load(&t);
    }

    static inline float4 load(const dfloat4 *p){
        return _mm_load_ps(&p->x);
    }
};

inline dfloat3::dfloat3(const float4 &s){
    float4::store(this,s);
}

inline dfloat4::dfloat4(const float4 &s){
    float4::store(this,s);
}

class sfloat4{
public:
    sfloat4(){
        //
    }

    sfloat4(const sfloat1 &n){
        //replicate
        v[0].v = FL_PERMUTE(n.v,_MM_SHUFFLE(0,0,0,0));//XMVectorSplat(n);
        v[1].v = FL_PERMUTE(n.v,_MM_SHUFFLE(1,1,1,1));//XMVectorSplatY(n);
        v[2].v = FL_PERMUTE(n.v,_MM_SHUFFLE(2,2,2,2));
        v[3].v = FL_PERMUTE(n.v,_MM_SHUFFLE(3,3,3,3));
    }

    sfloat4(const sfloat1 &a, const sfloat1 &b, const sfloat1 &c, const sfloat1 &d){
        set(0,a);
        set(1,b);
        set(2,c);
        set(3,d);
    }

    ~sfloat4(){
        //
    }

    inline sfloat4 operator+(const sfloat4 &s) const{
        sfloat4 r;
        r.v[0] = v[0]+s.v[0];
        r.v[1] = v[1]+s.v[1];
        r.v[2] = v[2]+s.v[2];
        r.v[3] = v[3]+s.v[3];
        return r;
    }

    inline void operator+=(const sfloat4 &s){
        v[0] += s.v[0];
        v[1] += s.v[1];
        v[2] += s.v[2];
        v[3] += s.v[3];
    }

    inline sfloat4 operator-(const sfloat4 &s) const{
        sfloat4 r;
        r.v[0] = v[0]-s.v[0];
        r.v[1] = v[1]-s.v[1];
        r.v[2] = v[2]-s.v[2];
        r.v[3] = v[3]-s.v[3];
        return r;
    }

    inline void operator-=(const sfloat4 &s){
        v[0] -= s.v[0];
        v[1] -= s.v[1];
        v[2] -= s.v[2];
        v[3] -= s.v[3];
    }

    inline sfloat4 operator*(const sfloat4 &s) const{
        sfloat4 r;
        r.v[0] = v[0]*s.v[0];
        r.v[1] = v[1]*s.v[1];
        r.v[2] = v[2]*s.v[2];
        r.v[3] = v[3]*s.v[3];
        return r;
    }

    inline void operator*=(const sfloat4 &s){
        v[0] *= s.v[0];
        v[1] *= s.v[1];
        v[2] *= s.v[2];
        v[3] *= s.v[3];
    }

    inline sfloat4 operator/(const sfloat4 &s) const{
        sfloat4 r;
        r.v[0] = v[0]/s.v[0];
        r.v[1] = v[1]/s.v[1];
        r.v[2] = v[2]/s.v[2];
        r.v[3] = v[3]/s.v[3];
        return r;
    }

    inline void operator/=(const sfloat4 &s){
        v[0] /= s.v[0];
        v[1] /= s.v[1];
        v[2] /= s.v[2];
        v[3] /= s.v[3];
    }

    inline sfloat4 operator*(const sfloat1 &s) const{
        sfloat4 r;
        r.v[0] = v[0]*s;
        r.v[1] = v[1]*s;
        r.v[2] = v[2]*s;
        r.v[3] = v[3]*s;
        return r;
    }

    inline void operator*=(const sfloat1 &s){
        v[0] *= s;
        v[1] *= s;
        v[2] *= s;
        v[3] *= s;
    }

    inline sfloat4 operator/(const sfloat1 &s) const{
        sfloat4 r;
        r.v[0] = v[0]/s;
        r.v[1] = v[1]/s;
        r.v[2] = v[2]/s;
        r.v[3] = v[3]/s;
        return r;
    }

    inline void operator/=(const sfloat1 &s){
        v[0] /= s;
        v[1] /= s;
        v[2] /= s;
        v[3] /= s;
    }

    template<uint x, uint y, uint z, uint w>
    inline sfloat4 swizzle() const{
        sfloat4 r;
        r.v[0] = v[x];
        r.v[1] = v[y];
        r.v[2] = v[z];
        r.v[3] = v[w];
        return r;
    }

    template<uint x>
    inline float4 get() const{
        return sfloat1::select(
            sfloat1::select(sfloat1::splat<x>(v[0]),sfloat1::splat<x>(v[1]),sfloat1::selectctrl(0,1,0,1)),
            sfloat1::select(sfloat1::splat<x>(v[2]),sfloat1::splat<x>(v[3]),sfloat1::selectctrl(0,1,0,1)),sfloat1::selectctrl(0,0,1,1)).v;
    }

    inline float4 get(uint x) const{
        return sfloat1::select(
            sfloat1::select(v[0].splat(x),v[1].splat(x),sfloat1::selectctrl(0,1,0,1)),
            sfloat1::select(v[2].splat(x),v[3].splat(x),sfloat1::selectctrl(0,1,0,1)),sfloat1::selectctrl(0,0,1,1)).v;
    }

    inline void set(uint x, const float4 &s){
        sfloat1 c = sfloat1::selectctrl(x == 0,x == 1,x == 2,x == 3);
        v[0] = sfloat1::select(v[0],s.splat<0>(),c);
        v[1] = sfloat1::select(v[1],s.splat<1>(),c);
        v[2] = sfloat1::select(v[2],s.splat<2>(),c);
        v[3] = sfloat1::select(v[3],s.splat<3>(),c);
    }

    inline sfloat4 xyz0() const{
        sfloat4 r;
        r.v[0] = v[0];
        r.v[1] = v[1];
        r.v[2] = v[2];
        r.v[3] = sfloat1::zero();
        return r;
    }

    static inline sfloat4 min(const sfloat4 &a, const sfloat4 &b){
        sfloat4 r;
        r.v[0] = sfloat1::min(a.v[0],b.v[0]);
        r.v[1] = sfloat1::min(a.v[1],b.v[1]);
        r.v[2] = sfloat1::min(a.v[2],b.v[2]);
        r.v[3] = sfloat1::min(a.v[3],b.v[3]);
        return r;
    }

    static inline sfloat4 max(const sfloat4 &a, const sfloat4 &b){
        sfloat4 r;
        r.v[0] = sfloat1::max(a.v[0],b.v[0]);
        r.v[1] = sfloat1::max(a.v[1],b.v[1]);
        r.v[2] = sfloat1::max(a.v[2],b.v[2]);
        r.v[3] = sfloat1::max(a.v[3],b.v[3]);
        return r;
    }

    static inline sfloat1 dot3(const sfloat4 &a, const sfloat4 &b){
        return a.v[0]*b.v[0]+a.v[1]*b.v[1]+a.v[2]*b.v[2];
    }

    static inline sfloat1 dot4(const sfloat4 &a, const sfloat4 &b){
        return a.v[0]*b.v[0]+a.v[1]*b.v[1]+a.v[2]*b.v[2]+a.v[3]*b.v[3];
    }

    static inline sfloat1 length3(const sfloat4 &v){
        return sfloat1::sqrt(dot3(v,v));
    }

    static inline sfloat4 normalize3(const sfloat4 &s){
        return s/length3(s);
    }

    static inline sfloat4 cross3(const sfloat4 &a, const sfloat4 &b){
        sfloat4 r;
        r.v[0] = a.v[1]*b.v[2]-a.v[2]*b.v[1];
        r.v[1] = a.v[2]*b.v[0]-a.v[0]*b.v[2];
        r.v[2] = a.v[0]*b.v[1]-a.v[1]*b.v[0];
        r.v[3] = sfloat1::zero();
        return r;
    }

    static inline sfloat4 floor(const sfloat4 &s){
        sfloat4 r;
        r.v[0] = sfloat1::floor(s.v[0]);
        r.v[1] = sfloat1::floor(s.v[1]);
        r.v[2] = sfloat1::floor(s.v[2]);
        r.v[3] = sfloat1::floor(s.v[3]);
        return r;
    }

    static inline sfloat4 ceil(const sfloat4 &s){
        sfloat4 r;
        r.v[0] = sfloat1::ceil(s.v[0]);
        r.v[1] = sfloat1::ceil(s.v[1]);
        r.v[2] = sfloat1::ceil(s.v[2]);
        r.v[3] = sfloat1::ceil(s.v[3]);
        return r;
    }

    static inline sfloat4 lerp(const sfloat4 &a, const sfloat4 &b, const sfloat1 &t){
        sfloat4 r;
        sfloat1 s = sfloat1::one()-t;
        r.v[0] = a.v[0]*s+b.v[0]*t;
        r.v[1] = a.v[1]*s+b.v[1]*t;
        r.v[2] = a.v[2]*s+b.v[2]*t;
        r.v[3] = a.v[3]*s+b.v[3]*t;
        return r;
    }

    sfloat1 v[4];
};

class sint1{
public:
    sint1(){
        //
    }

    sint1(int a){
        v = _mm_set1_epi32(a);
    }

    sint1(int x, int y, int z, int w){
        v = _mm_set_epi32(w,z,y,x);
    }

    sint1(const sfloat1 &s);

    sint1(const __m128i &_v){
        v = _v;
    }

    ~sint1(){
        //
    }

    /*inline sint1& operator=(const __m128i &r){
        v = r;
        return *this;
    }*/

    inline operator __m128i() const{
        return v;
    }

    static inline sint1 convert(const sfloat1 &s){
        return _mm_cvttps_epi32(s.v);
    }

    inline sint1 operator+(const sint1 &s) const{
        return _mm_add_epi32(v,s.v);
    }

    inline void operator+=(const sint1 &s){
        v = _mm_add_epi32(v,s.v);
    }

    inline sint1 operator-() const{
        return _mm_sub_epi32(_mm_setzero_si128(),v);
    }

    inline sint1 operator-(const sint1 &s) const{
        return _mm_sub_epi32(v,s.v);
    }

    inline void operator-=(const sint1 &s){
        v = _mm_sub_epi32(v,s.v);
    }

	static inline sint1 mask(int m){
		return _mm_set_epi32(
			m & (1<<3)?-1:0,
			m & (1<<2)?-1:0,
			m & (1<<1)?-1:0,
			m & (1<<0)?-1:0);
	}

    static inline sint1 Equal(const sint1 &a, const sint1 &b){
        return _mm_cmpeq_epi32(a.v,b.v);
    }

    static inline sint1 Greater(const sint1 &a, const sint1 &b){
        return _mm_cmpgt_epi32(a.v,b.v);
    }

    /*static inline sint1 GreaterOrEqual(const sint1 &a, const sint1 &b){
        sint1 r;
        r.v = _mm_cmpge_epi32(a.v,b.v);
        return r;
    }*/

    static inline sint1 Less(const sint1 &a, const sint1 &b){
		return _mm_cmplt_epi32(a.v,b.v);
    }

    /*static inline sint1 LessOrEqual(const sint1 &a, const sint1 &b){
        sint1 r;
        r.v = _mm_cmple_epi32(a.v,b.v);
        return r;
    }*/

    static inline sint1 And(const sint1 &a, const sint1 &b){
        return _mm_and_si128(a.v,b.v);
    }

    static inline sint1 AndNot(const sint1 &a, const sint1 &b){
        return _mm_andnot_si128(a.v,b.v);
    }

    static inline sint1 Or(const sint1 &a, const sint1 &b){
        return _mm_or_si128(a.v,b.v);
    }

    static inline void store(int *pdst, const sint1 &s){
        _mm_store_si128(reinterpret_cast<__m128i*>(pdst),s.v);
    }

    static inline sint1 load(const int *psrc){
        return _mm_load_si128(reinterpret_cast<const __m128i*>(psrc));
    }

	static inline void store(dintN *pdst, const sint1 &s){
        _mm_store_si128(reinterpret_cast<__m128i*>(pdst),s.v);
    }

    static inline sint1 load(const dintN *psrc){
        return _mm_load_si128(reinterpret_cast<const __m128i*>(psrc));
    }

    __m128i v;
};

class sint4{
public:
    sint4(){
        //
    }

    sint4(const sint1 &n){
        //replicate
        v[0].v = IL_PERMUTE(n.v,_MM_SHUFFLE(0,0,0,0));//XMVectorSplatX(n);
        v[1].v = IL_PERMUTE(n.v,_MM_SHUFFLE(1,1,1,1));//XMVectorSplatY(n);
        v[2].v = IL_PERMUTE(n.v,_MM_SHUFFLE(2,2,2,2));
        v[3].v = IL_PERMUTE(n.v,_MM_SHUFFLE(3,3,3,3));
    }

    //set constructor

    sint4(const sfloat4 &s){
        v[0] = sint1(s.v[0]);
        v[1] = sint1(s.v[1]);
        v[2] = sint1(s.v[2]);
        v[3] = sint1(s.v[3]);
    }

    ~sint4(){
        //
    }

    static inline sint4 convert(const sfloat4 &s){
        sint4 r;
        r.v[0] = sint1::convert(s.v[0]);
        r.v[1] = sint1::convert(s.v[1]);
        r.v[2] = sint1::convert(s.v[2]);
        r.v[3] = sint1::convert(s.v[3]);
        return r;
    }

    inline sint4 operator+(const sint4 &s) const{
        sint4 r;
        r.v[0] = v[0]+s.v[0];
        r.v[1] = v[1]+s.v[1];
        r.v[2] = v[2]+s.v[2];
        r.v[3] = v[3]+s.v[3];
        return r;
    }

    inline void operator+=(const sint4 &s){
        v[0] += s.v[0];
        v[1] += s.v[1];
        v[2] += s.v[2];
        v[3] += s.v[3];
    }

    inline sint4 operator-(const sint4 &s) const{
        sint4 r;
        r.v[0] = v[0]-s.v[0];
        r.v[1] = v[1]-s.v[1];
        r.v[2] = v[2]-s.v[2];
        r.v[3] = v[3]-s.v[3];
        return r;
    }

    inline void operator-=(const sint4 &s){
        v[0] -= s.v[0];
        v[1] -= s.v[1];
        v[2] -= s.v[2];
        v[3] -= s.v[3];
    }

    static sint4 And(const sint4 &a, const sint4 &b){
        sint4 r;
        r.v[0] = sint1::And(a.v[0],b.v[0]);
        r.v[1] = sint1::And(a.v[1],b.v[1]);
        r.v[2] = sint1::And(a.v[2],b.v[2]);
        r.v[3] = sint1::And(a.v[3],b.v[3]);
        return r;
    }

    sint1 v[4];
};

inline sfloat1::sfloat1(const sint1 &s){
    v = _mm_castsi128_ps(s.v);
}

inline sint1::sint1(const sfloat1 &s){
    v = _mm_castps_si128(s.v); //no conversion
    //v = _mm_cvttps_epi32(s.v); //truncate
}

inline dintN::dintN(const sint1 &s){
	sint1::store(v,s);
}

class matrix44{
public:
    matrix44(){}
    matrix44(__m128 *p){
        r[0].v = p[0];
        r[1].v = p[1];
        r[2].v = p[2];
        r[3].v = p[3];
    }

    static inline void store(dmatrix44 *p, const matrix44 &m){
        float4::store(&p->r[0],m.r[0]);
        float4::store(&p->r[1],m.r[1]);
        float4::store(&p->r[2],m.r[2]);
        float4::store(&p->r[3],m.r[3]);
    }

    static inline matrix44 load(const dmatrix44 *p){
        matrix44 r;
        r.r[0] = float4::load(&p->r[0]);
        r.r[1] = float4::load(&p->r[1]);
        r.r[2] = float4::load(&p->r[2]);
        r.r[3] = float4::load(&p->r[3]);
        return r;
    }

    float4 r[4];
};

#endif // SMMATH_INL
