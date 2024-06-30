#include "Cloud.hlsli"

//  ���͒l
struct Input
{
    float4 Position     : SV_Position;
    float3 Normal       : NORMAL;
    float2 TexCoord     : TEXCOORD0;
    float4 Color        : COLOR;
};
//  �o�͒l
struct Output
{
    float3 NormalWS     : TEXCOORD0;    //  �@��
    float4 PositionPS   : SV_Position;  //  ���e��Ԃ̍��W
};

//  �~����
#define PI 3.1415926535f
//  �d�͉����x
#define GRAVITY 9.8f

// �Q���X�g�i�[�g
void gerstnerWave(
    in float3 localVtx,
    float t,
    float waveLen,
    float Q,
    float R,
    float2 browDir,
    inout float3 localVtxPos,
    inout float3 localNormal
)
{
    browDir = normalize(browDir);
    float A = waveLen / 14.0f;
    float _2pi_per_L = 2.0f * PI / waveLen;
    float d = dot(browDir, localVtx.xz);
    float th = _2pi_per_L * d + sqrt(GRAVITY / _2pi_per_L) * t;

    float3 pos = float3(0.0, R * A * sin(th), 0.0);
    pos.xz = Q * A * browDir * cos(th);

    // �Q���X�g�i�[�g�̖@��
    float3 normal = float3(0.0, 1.0, 0.0);
    normal.xz = -browDir * R * cos(th) / (7.0f / PI - Q * browDir * browDir * sin(th));

    localVtxPos += pos;
    localNormal += normalize(normal);
}

Output main(Input vin)
{
    Output output;

    vin.Position.xz *= 10.0f;
    vin.Position.y *= 0.5f;

    float t = LightDir.w;
    float3 oPosW = float3(0.0, 0.0, 0.0);
    float3 oNormalW = float3(0.0, 0.0, 0.0);
    gerstnerWave(vin.Position.xyz, t + 2.0, 0.8, 0.7, 0.3, float2(0.2, 0.3), oPosW, oNormalW);
    gerstnerWave(vin.Position.xyz, t, 1.2, 0.3, 0.5, float2(-0.4, 0.7), oPosW, oNormalW);
    gerstnerWave(vin.Position.xyz, t + 3.0, 1.8, 0.3, 0.5, float2(0.4, 0.4), oPosW, oNormalW);
    vin.Position.xyz += oPosW;

    // ���_�̈ʒu�𓊉e��Ԃ�
    output.PositionPS = mul(vin.Position, WorldViewProj);
    // �@���x�N�g�������[���h��Ԃցi�g��k���̉e����ł��������ߋt�]�u�s���������j
    output.NormalWS = oNormalW;
 
    return output;
}