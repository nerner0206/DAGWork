#include "Cloud.hlsli"

//  ���͒l
struct Input
{
    float3 NormalWS     : TEXCOORD0;    //  �@��
};

float4 main(Input pin) : SV_TARGET0
{
    // �@���𐳋K��
    float3 worldNormal = normalize(pin.NormalWS);
    // ���̋�������ς���Z�o����
    float dotL = dot(-normalize(LightDir.xyz), worldNormal);
    // �\�ʂ̏ꍇ�͂P�A���ʂ̏ꍇ��0
    float zeroL = step(0, dotL);
    // ���ʂ̏ꍇ�͍��ɂȂ�
    float diffuse = zeroL * dotL;

    return float4(diffuse, diffuse, diffuse, 1.0f);
}