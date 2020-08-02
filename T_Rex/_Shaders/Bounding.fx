float4 LineColor;

cbuffer CB_PerFrame
{
    matrix View;
    matrix Projection;
}

matrix World;

//-----------------------------------------------------------------------------
//Types
//-----------------------------------------------------------------------------
struct VertexInput
{
    float4 Position : POSITION0; // 0 안붙여도 됨 인덱스 알아서 추가한다
};

struct VertexOutput
{
    float4 Position : SV_POSITION0; // SV_가 붙어야지 레스터화 과정에 참여 가능하다
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

    return output;
}

//-----------------------------------------------------------------------------
//Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(VertexOutput input) : SV_TARGET0
{
    return LineColor;
}

//-----------------------------------------------------------------------------
//PipeLine
//-----------------------------------------------------------------------------
technique11 T0  //컴파일을 여기서 해줌
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS())); // VS() 위에 함수 이름과 같아야 한다
        SetPixelShader(CompileShader(ps_5_0, PS()));  // PS() 위에 함수 이름과 같아야 한다
    }
}