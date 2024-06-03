#include <corecrt_math.h>
#include <format>
#include <imgui.h>
#include <Novice.h>

#include "Camera.h"
#include "config.h"
#include "Math/Vec3/Vec3.h"
#include "Object/Object.h"

constexpr char kWindowTitle[] = "LE2B_24_ミズサワ_ハミル_TR1_PhysicsConstraint";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kClientWidth, kClientHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	bool isShowBoundingBox = false;

	std::vector<std::shared_ptr<Object>> objects;

	auto object = std::make_shared<Object>("object");
	object->Initialize("Object");
	auto object2 = std::make_shared<Object>("object2");
	object2->Initialize("Object2");
	object->AddChild(object2);
	objects.push_back(object);

	auto camera = std::make_shared<Camera>("Camera");
	camera->Initialize("Camera");
	camera->SetTransform(
		{ {0.0f,0.0f,0.0f},
		{0.0f,0.01f,0.0f},
		{1.0f,1.0f,1.0f} }
	);

	objects.push_back(camera);

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

		for (auto o : objects) {
			o->Update();
		}

		camera->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vec3 pos = Mat4::Transform(Mat4::Transform(object->GetTransform().position, camera->GetProjectionMatrix()), camera->getViewMatrix());

		Novice::DrawEllipse(
			static_cast<int>(pos.x), static_cast<int>(pos.y),
			8, 8,
			0.0f,
			RED,
			kFillModeSolid
		);

		ImGui::ShowDemoWindow();

		ImGui::Begin("Outliner");

		for (auto o : objects) {
			if (ImGui::TreeNode(std::format("{}", o->GetName()).c_str())) {

				for (auto& child : o->GetChildren()) {

					if (ImGui::TreeNode(std::format("{}", child->GetName()).c_str())) {

						ImGui::TreePop();
					}
				}

				ImGui::TreePop();
			}
		}

		ImGui::End();

		ImGui::Begin("Details");

		if (ImGui::BeginTabBar("Object")) {
			if (ImGui::BeginTabItem("Object")) {
				if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
					Transform tmp = object->GetTransform();

					ImGui::DragFloat3("Location", &tmp.position.x, 0.01f);
					ImGui::DragFloat3("Rotation", &tmp.rotation.x, 0.01f);
					ImGui::DragFloat3("Scale", &tmp.scale.x, 0.01f);
					object->SetTransform(tmp);
				}

				if (ImGui::CollapsingHeader("Debug", ImGuiTreeNodeFlags_DefaultOpen)) {
					ImGui::Checkbox("Show bounding box", &isShowBoundingBox);
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Camera")) {
				Transform tmp = camera->GetTransform();

				ImGui::DragFloat3("Location", &tmp.position.x, 0.01f);
				ImGui::DragFloat3("Rotation", &tmp.rotation.x, 0.01f);
				ImGui::DragFloat3("Scale", &tmp.scale.x, 0.01f);
				camera->SetTransform(tmp);

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
