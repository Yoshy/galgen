#pragma once

#include <memory>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Scene/Scene.h>

const float SPHERE_SCALE{ 0.005f };
const float CAMERA_DEFAULT_DISTANCE{ 1.0f };

using namespace Urho3D;

class GalaxyViewer : public Application
{
	URHO3D_OBJECT(GalaxyViewer, Application);
public:
	explicit GalaxyViewer(Context * context);
	void Setup() final;
	void Start() final;
	void Stop() final;
	void HandleUpdate(StringHash eventType, VariantMap& eventData);
	void HandleKeyDown(StringHash eventType, VariantMap& eventData);
private:
	SharedPtr<Scene> scene_;
	SharedPtr<Node> cameraNode_;
	bool isCameraOrtho;
	float cameraYaw_;
	float cameraPitch_;
	float cameraRoll_;
	void CreateScene_();
	void RegenerateGalaxy_();
	void SetCameraLookAt(const Vector3& v);
	void AddDirectionalLight(const Vector3& direction);
	Node* AddObject_(const Vector3& position, float size, const String& material);
};
