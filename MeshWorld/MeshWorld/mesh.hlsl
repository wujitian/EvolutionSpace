struct Vertex
{
    float3 position : POSITION;
};

struct MSOutput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

[numthreads(1, 1, 1)]
[outputtopology("triangle")]
//[patchconstantfunc("GetOutputCounts")]
void MSMain(uint3 threadID : SV_GroupThreadID, inout vertices Vertex outVertices[3], out indices uint outIndices[3])
{
    // Set output vertex and index counts
    SetMeshOutputCounts(3, 1);

    // Define triangle vertices
    outVertices[0].position = float3(0.0, 0.5, 0.0);
    outVertices[1].position = float3(0.5, -0.5, 0.0);
    outVertices[2].position = float3(-0.5, -0.5, 0.0);

    // Define triangle indices
    outIndices[0] = 0;
    outIndices[1] = 1;
    outIndices[2] = 2;
}

[shader("pixel")]
float4 PSMain(MSOutput input) : SV_Target
{
    return float4(0.0f, 1.0f, 0.0f, 1.0f); // Green color
}