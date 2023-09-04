#include "Framework.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture()
{
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	// DESC �ʱ�ȭ
	{
		// ���� ���� ũ��
		textureDesc.Width = WinMaxWidth;
		textureDesc.Height = WinMaxHeight;
		// �ؽ�ó ���İ� ��� �뵵
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		// � ���ҽ��� ���ε����� ����
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		// ��Ƽ ���ø��� ������ ���, ���ø��� ���� ������ ����
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		// �Ӹ� ���� ���� ���� (�Ӹ� : �ϳ��� �ؽ�ó �̹����� ���� �ػ󵵷� ����� �����ϴ� �۾�)
		textureDesc.MipLevels = 1;
		// �ؽ�ó �迭 ũ�� (1�� �����ϸ� ���� �ؽ�ó)
		textureDesc.ArraySize = 1;
		// ��Ÿ �ؽ�ó �ɼ�
		textureDesc.MiscFlags = 0;
	}

	HRESULT hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, &texture);
	CHECK(hr);


	// Render Target View
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));

	// Desc ����
	{
		rtvDesc.Format = textureDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;
	}

	// RTV ����
	hr = DEVICE->CreateRenderTargetView(texture, &rtvDesc, &rtv);
	CHECK(hr);


	// Shader Resource View
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	// DESC ����
	{
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
	}

	// SRV ����
	hr = DEVICE->CreateShaderResourceView(texture, &srvDesc, &srv);
	CHECK(hr);
}

RenderTexture::~RenderTexture()
{
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(texture);
}

void RenderTexture::RenderToTexture()
{
	// Om �ܰ迡�� ����� RTV �� ����-���ٽ� �� ����
	DC->OMSetRenderTargets(1, &rtv, nullptr);
	DC->ClearRenderTargetView(rtv, ClearColor);
}

/*
Texture2D
- �׷��� ī�忡�� ����ϴ� �ؽ�ó �����͸� �����ϴ� ��ü
- �ַ� �̹���, ����, ������, ����Ʈ�ʵ��� ����
- ũ��, ����, �Ӹ�, ��Ƽ ���ø� �� �پ��� �Ӽ��� ���� �� �ִ�

Shader Resource View
- �ؽ�ó�� ���̴����� �б� ���� ��
- ���̴��� �ؽ�ó�� �о �ȼ��� ���� ���
- SRV�� ����Ͽ� ���̴��� �ؽ�ó �����Ϳ� ������ �� �� �ִ�

Render Target View
- ���� Ÿ�ٿ� ���� ��
- ���̴� ����� �����ϴ� ����
- �ش� ���ۿ� ���� �б�/���� �������� ����
- ���̴� ����� ���� Ÿ�ٿ� ������ �� �ִ�

view
- ���ҽ��� Ư�� �κ��̳� Ư�� ������� �ؼ��� �����͸� �����ϴ� ��ü

MipMap
- DirectX���� �Ʒ��� ������ ���ؼ� �ؽ�ó�� ���� �ػ� ������ �����ϴ� �̹��� �÷�������, ������ �ػ� ������ �迭�� ����
- �ؽ�ó ������ ���� ȿ�������� �̷����
	- 3D �������� ��ü�� ȭ�鿡 �������� ũ�� ���̰�, �ָ� �������� �۰� ���δ�
	- ����� ��ü���� ���� �ػ��� �ؽ�ó�� �����ϰ�, �ָ� �ִ� ��ü���� ���� �ػ��� �ؽ�ó�� �����Ѵ�
		-> �ڿ� ��뷮�� �پ��� ������ �ӵ��� ������
*/