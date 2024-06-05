#include <corecrt_math.h>
#include <format>
#include <imgui.h>
#include <Novice.h>

#include "Config.h"
#include "Math/Vec3/Vec3.h"
#include "Object/Base/Object.h"
#include "Camera.h"
#include "Object/Circle.h"

constexpr char kWindowTitle[] = "LE2B_24_ミズサワ_ハミル_TR1_PhysicsConstraint";

void RenderOutliner(const std::shared_ptr<Object>& object, std::shared_ptr<Object>& selectedObject) {
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

	if (object->GetChildren().empty()) {
		nodeFlags |= ImGuiTreeNodeFlags_Leaf;
	}

	if (object == selectedObject) {
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	}

	bool nodeOpen = ImGui::TreeNodeEx(object->GetName().c_str(), nodeFlags);

	if (ImGui::IsItemClicked()) {
		selectedObject = object;
	}

	if (nodeOpen && !object->GetChildren().empty()) {
		for (const auto& child : object->GetChildren()) {
			RenderOutliner(child, selectedObject);
		}
		ImGui::TreePop();
	} else if (nodeOpen) {
		ImGui::TreePop();
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kClientWidth, kClientHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ワールドにあるすべてのオブジェクトを格納します
	std::vector<std::shared_ptr<Object>> objects;

	auto circle = std::make_shared<Circle>("Circle");
	objects.push_back(circle);

	// // オブジェクトを複数作成し、子オブジェクトも追加
	// for (int i = 0; i < 5; ++i) {
	// 	auto parent = std::make_shared<Object>("Parent" + std::to_string(i + 1));
	// 	for (int j = 0; j < rand() % 6; ++j) {
	// 		auto child = std::make_shared<Object>("Child" + std::to_string(i + 1) + "-" + std::to_string(j + 1));
	// 		parent->AddChild(child);
	// 	}
	// 	objects.push_back(parent);
	// }

	// カメラを作成
	auto camera = std::make_shared<Camera>();
	camera->Initialize("Camera");
	camera->SetTransform(
		{
			{0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f},
			{1.0f, 1.0f, 1.0f}
		}
	);
	objects.push_back(camera);

	// 選択されたオブジェクトのポインタがここに格納される
	std::shared_ptr<Object> selectedObject = nullptr;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// オブジェクトの更新
		for (auto o : objects) {
			o->Update();
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::ShowDemoWindow();

		for (const auto& o : objects) {
			o->Draw(*camera);
		}

		ImGui::Begin("Outliner");

		for (const auto& o : objects) {
			RenderOutliner(o, selectedObject);
		}

		ImGui::End();

		ImGui::Begin("Details");

		if (ImGui::BeginTabBar("Object")) {
			if (ImGui::BeginTabItem("Object")) {
				if (selectedObject != nullptr) {
					selectedObject->Details();
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("World")) {
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
