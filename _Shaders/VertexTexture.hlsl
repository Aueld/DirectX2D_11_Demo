// VertexInput ����ü ����
struct VertexInput
{
    float4 position : POSITION0;    // ���� ��ġ    "position"�̶�� ������ "POSITION0" ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�
    float2 uv : TEXCOORD0;          // uv ��ǥ    
};

// PixelInput ����ü ����
struct PixelInput
{
    float4 position : SV_POSITION0; // �ȼ� ��ġ    �ȼ��� ��ġ�� ��Ÿ���� �ý��� ���� �ǹ�
    float2 uv : TEXCOORD0;          // �ȼ� ����
};

// ��� ���� �������� b0�� �Ҵ�� ���� ����� �����ϴ� ��� ����
cbuffer WorldBuffer : register(b0) // 0 ~ 127
{
    matrix _world;
};

// ��� ���� �������� b1�� �Ҵ�� �� ��İ�, �������� ����� �����ϴ� ��� ����
cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
};

// ���� ���̴� �Լ�
// �Է����� VertexInput�� �ް� PixelInput ����ü�� ��ȯ
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);          // ���� ��ġ�� ���� ����� ����
    output.position = mul(output.position, _view);          // ����� �� ����� ����
    output.position = mul(output.position, _projection);    // ����� �������� ��Ʈ���� ����
    
    output.uv = input.uv;
    return output;
}

Texture2D _sourceTex : register(t0);    // �ؽ�ó �����͸� ����, �ؽ�ó ���� 0���� ���ε�
SamplerState _samp : register(s0);      // ���ø��ϴ� ����� ����, ���÷� ���� 0���� ���ε�

// �ȼ� ���̴� �Լ�
// �Է����� PixelInput ����ü�� �ް�, float4 ������ �ȼ� ������ ��ȯ
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    
    return color;
}

/*
Semantic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴ� �� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����ϸ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

System-Value Semantic : �ý��� �� ����ƽ
1. SV_Position  : ���� ���̴� ��¿��� �ȼ� ���̴� �Է����� Ŭ�� ���� ��ġ ������ �����ϴµ� ���
2. SV_Target    : �ȼ� ���̴��� ��¿��� ���� Ÿ������ ���� ������ �����ϴ� �� ���
3. SV_Depth     : �ȼ� ���̴��� ��¿��� ���� ���۷� ���� ������ �����ϴ� �� ���
(�ڼ��� ������ Direct3D ���� ����)

slot
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ���������� ������ �� ����
- �ֿ� ����
    1) ��� ���� ����
    - ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS���� ������ �� �ִ�
    - ��� ���� ������ register(b#)�� ����Ͽ� ����
    
    2) �ؽ�ó ����
    - �̹��� �����͸� �����ϴµ� ���
    - �ؽ�ó ���� ������ register(t#)�� ����Ͽ� ����

    3) ���÷� ����
    - �ؽ�ó�� ���ø��ϴ� �� ���
    - ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constant Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� ����
- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�

Sampler : ���÷�
- �ؽ�ó���� �ȼ� ���� �������� ����� �����ϴ� ��ü
- �ؽ�ó ���ø��� �ؽ�ó �̹����� ���� �ؼ� ���� ����ϴ� �۾�
  (�ؼ� : �ؽ�ó�� �ȼ� ��)
*/