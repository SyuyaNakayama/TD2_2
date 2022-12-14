#pragma once
#include "FbxModel.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class FbxObject3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public: // サブクラス
	// 定数バッファ用データ構造体（座標変換行列用）
	struct ConstBufferDataTransform
	{
		Matrix4 viewproj;    // ビュープロジェクション行列
		Matrix4 world; // ワールド行列
		Vector3 cameraPos; // カメラ座標（ワールド座標）
	};

public: // 静的メンバ関数
	static ViewProjection* viewProjection;
	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();
	// setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device = device; }
	static void SetViewProjection(ViewProjection* viewProjection) { FbxObject3d::viewProjection = viewProjection; }

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WorldTransform* worldTransform);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void SetModel(FbxModel* model) { this->model = model; }

protected: // メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	WorldTransform* worldTransform;
	// モデル
	FbxModel* model = nullptr;
};

