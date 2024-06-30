Texture2D<float4> Texture   : register(t0);
sampler Sampler             : register(s0);


cbuffer Parameters : register(b0)
{
    float4x4 World                  : packoffset(c15);
    float3x3 WorldInverseTranspose  : packoffset(c19);
    float4x4 WorldViewProj          : packoffset(c22);
};

// 追加する定数バッファ
cbuffer Parameters : register(b1)
{
    float4x4 LightViewProj  : packoffset(c0);
    float4 LightPos         : packoffset(c4);
    float4 LightDir     : packoffset(c5);
};