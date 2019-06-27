struct Light
{
    float3 dir;
    float4 ambient;
    float4 diffuse;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

cbuffer PS_LIGHT
{
    Light light;
};

struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};
float4 main(PixelShaderInput IN) : SV_TARGET
{
    IN.normal = normalize(IN.normal);

    float4 diffuse = ObjTexture.Sample(ObjSamplerState, IN.TexCoord);

    float3 finalColor;

    finalColor = diffuse * light.ambient ;
    finalColor += saturate(dot(light.dir, IN.normal) * light.diffuse * diffuse);
    
    return float4(finalColor, diffuse.a);
}
