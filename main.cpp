#include <corecrt_math.h>
#include <imgui.h>
#include <Novice.h>

#include "Math/Vec3/Vec3.h"
#include "Object/Object.h"

constexpr char kWindowTitle[] = "LE2B_24_ミズサワ_ハミル_TR1_PhysicsConstraint";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	bool isShowBoundingBox = false;

	Object* object = new Object();
	

	
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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::ShowDemoWindow();

		ImGui::Begin("Outliner");

		ImGui::Text("Hello ImGui!!");

		ImGui::End();

		ImGui::Begin("Details");

		if (ImGui::BeginTabBar("Object")) {
			if (ImGui::BeginTabItem("Object")) {
				ImGui::SetNextItemOpen(true);
				if (ImGui::CollapsingHeader("Transform")) {
					ImGui::DragFloat3("Location", &object->GetTransform().position.x, 0.01f);
					ImGui::DragFloat3("Rotation", &object->GetTransform().rotation.x, 0.01f);
					ImGui::DragFloat3("Scale", &object->GetTransform().scale.x, 0.01f);
				}

				ImGui::SetNextItemOpen(true);
				if (ImGui::CollapsingHeader("Debug")) {
					ImGui::Checkbox("Show bounding box", &isShowBoundingBox);
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

	delete object;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
