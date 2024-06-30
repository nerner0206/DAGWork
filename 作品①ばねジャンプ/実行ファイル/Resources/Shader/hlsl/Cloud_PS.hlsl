#include "Cloud.hlsli"

//  入力値
struct Input
{
    float3 NormalWS     : TEXCOORD0;    //  法線
};

float4 main(Input pin) : SV_TARGET0
{
    // 法線を正規化
    float3 worldNormal = normalize(pin.NormalWS);
    // 光の強さを内積から算出する
    float dotL = dot(-normalize(LightDir.xyz), worldNormal);
    // 表面の場合は１、裏面の場合は0
    float zeroL = step(0, dotL);
    // 裏面の場合は黒になる
    float diffuse = zeroL * dotL;

    return float4(diffuse, diffuse, diffuse, 1.0f);
}