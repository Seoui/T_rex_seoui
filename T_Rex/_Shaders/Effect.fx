cbuffer CB_PerFrame
{
    matrix View;
    matrix Projection;
}
bool Scalar;
matrix World;

//-----------------------------------------------------------------------------
//Types
//-----------------------------------------------------------------------------
struct VertexInput
{
    float4 Position : POSITION0; // 0 안붙여도 됨 인덱스 알아서 추가한다
    float2 Uv : UV0;
};

struct VertexOutput
{
    float4 Position : SV_POSITION0; // SV_가 붙어야지 레스터화 과정에 참여 가능하다
    float2 Uv : UV0;
};

//-----------------------------------------------------------------------------
//Vertex Shader  공간변환을 여기서 해준다. W, V, P가 셰이더로 넘어와야 한다.
//-----------------------------------------------------------------------------
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;

    return output;
}

//-----------------------------------------------------------------------------
//Pixel Shader
//-----------------------------------------------------------------------------
Texture2D DiffuseMap;
SamplerState Sampler;

float4 PS(VertexOutput input) : SV_TARGET0
{
    
     if(Scalar)
     {
         return DiffuseMap.Sample(Sampler, input.Uv);
     }
     else
     {
         float4 test = DiffuseMap.Sample(Sampler, input.Uv);
         float1 gray = (test.r + test.g + test.b) * 0.333f;
         return float4(gray, gray, gray, test.a);
     }
    
    
}

//-----------------------------------------------------------------------------
//States
//-----------------------------------------------------------------------------
BlendState AlphaBlend
{
    BlendEnable[0] = true;
    DestBlend[0] = INV_SRC_ALPHA;
    SrcBlend[0] = SRC_ALPHA;
    BlendOp[0] = Add;

    SrcBlendAlpha[0] = One;
    DestBlendAlpha[0] = One;
    RenderTargetWriteMask[0] = 0x0F;
};

RasterizerState Cull
{
    CullMode = None;
    DepthClipEnable = false;
};

//-----------------------------------------------------------------------------
//PipeLine
//-----------------------------------------------------------------------------
technique11 T0  //컴파일을 여기서 해줌
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS())); // VS() 위에 함수 이름과 같아야 한다
        SetPixelShader(CompileShader(ps_5_0, PS()));  // PS() 위에 함수 이름과 같아야 한다

        SetRasterizerState(Cull);
        SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF);
    }
}

