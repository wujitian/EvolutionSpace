// Vertex shader
struct VSInput
{
    float3 position : POSITION;
};

struct PSInput
{
    float4 position : SV_POSITION;
};

PSInput VSMain(VSInput input)
{
    PSInput output;
    output.position = float4(input.position, 1.0f);
    return output;
}

// Pixel shader
float4 PSMain(PSInput input) : SV_Target
{
    return float4(0.0f, 1.0f, 0.0f, 1.0f);  // Green color
}
