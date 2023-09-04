// ������ �ε����� �����ϴ� ����

#pragma once

class IndexBuffer
{
public:
	~IndexBuffer();

	void Create(const vector<uint>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }
	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	uint stride = 0;
	uint offset = 0;
	uint count = 0;
};

/*
InputLayout
- ���� ������ ������ ������ ����
- ���� �������� �� ���(��ġ, ����, �ؽ�ó ��ǥ ��)�� ����, ũ��, ���� ���� ����
- IA �ܰ迡�� ���� ���̴��� �����͸� �����ϱ� ���� ���� �����͸� �ùٸ��� �ؼ��ϴµ� ���
*/