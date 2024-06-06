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

	Novice::SetWindowMode(kFullscreen);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ワールドにあるすべてのオブジェクトを格納します
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Circle>> circles;


	// // グリッド配置
	//const int x = 8; // x方向のCircleの数
	//const int y = 8; // y方向のCircleの数
	//const float spacing = 50.0f; // Circle間のスペース

	//for (int i = 0; i < x; ++i) {
	//	for (int j = 0; j < y; ++j) {
	//		auto circle = std::make_shared<Circle>("Circle_" + std::to_string(i) + "_" + std::to_string(j));
	//		circle->SetTransform(
	//			{
	//				{spacing * i, spacing * j, 0.0f},
	//				Vec3::zero,
	//				Vec3::one
	//			}
	//		);
	//		circle->Initialize(circle->GetName());
	//		circles.push_back(circle);
	//		objects.push_back(circle);
	//	}
	//}

	constexpr int numChildren = 5;
	auto circleRoot = std::make_shared<Circle>("CircleRoot");
	circleRoot->SetTransform(
		{
			Vec3::zero,
			Vec3::zero,
			Vec3::one
		}
	);
	circles.push_back(circleRoot);
	objects.push_back(circleRoot);

	auto parent = circleRoot;
	for (int i = 1; i <= numChildren; ++i) {
		auto child = std::make_shared<Circle>("child" + std::to_string(i));
		child->SetTransform(
			{
				{child->GetRadius() * 2.0f * i, 0.0f, 0.0f},
				Vec3::zero,
				Vec3::one
			}
		);
		parent->AddChild(child);
		child->Initialize(child->GetName());
		circles.push_back(child);
		parent = child;
	}

	auto otherCircle = std::make_shared<Circle>("OtherCircle");
	circles.push_back(otherCircle);
	objects.push_back(otherCircle);

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

	bool lookAtObject = true;

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

		// 円の更新
		for (size_t i = 0; i < circles.size(); ++i) {
			for (size_t j = i + 1; j < circles.size(); ++j) {
				if (circles[i]->IsCollide(*circles[j])) {
					circles[i]->ResolveCollision(*circles[j]);
				}
			}
		}

		// オブジェクトの更新
		for (auto& o : objects) {
			o->Update();
		}

		if (lookAtObject) {
			Transform newCameraTransform = {
				Vec3::Lerp(camera->GetTransform().position,
						   selectedObject != nullptr ? selectedObject->GetTransform().position : Vec3::zero,
						   10.0f * deltaTime),
				Vec3::zero,
				Vec3::one
			};

			camera->SetTransform(newCameraTransform);
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
				ImGui::DragFloat("Gravity", &gravity, 1.0f);
				ImGui::Checkbox("Look at Object", &lookAtObject);
				ImGui::Checkbox("DrawDebug", &bDrawDebug);
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
