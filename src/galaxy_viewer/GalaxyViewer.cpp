#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Engine/EngineDefs.h>

#include <vector>

#include "GalaxyViewer.h"
#include "GalaxyGenerator.h"


using namespace Urho3D;

GalaxyViewer::GalaxyViewer(Context * context) : Application(context), cameraYaw_(0.0f), cameraPitch_(0.0f), cameraRoll_(0.0f), isCameraOrtho(false)
{
}

void GalaxyViewer::Setup()
{
	engineParameters_[EP_FULL_SCREEN] = false;
	engineParameters_[EP_WINDOW_WIDTH] = 800;
	engineParameters_[EP_WINDOW_HEIGHT] = 600;
	engineParameters_[EP_WINDOW_RESIZABLE] = true;
	engineParameters_[EP_RESOURCE_PREFIX_PATHS] = String::EMPTY;
	engineParameters_[EP_RESOURCE_PATHS] = "Data;CoreData";
}

void GalaxyViewer::Start()
{
	// Setup window
	auto* cache { GetSubsystem<ResourceCache>() };
	auto* graphics { GetSubsystem<Graphics>() };
	auto icon { cache->GetResource<Image>("GGenIcon.png") };
	graphics->SetWindowIcon(icon);
	graphics->SetWindowTitle("Galaxy Generator");

	CreateScene_();
	RegenerateGalaxy_();
	
	// Subscribe to events
	SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(GalaxyViewer, HandleKeyDown));
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(GalaxyViewer, HandleUpdate));	
}

void GalaxyViewer::Stop()
{
}

void GalaxyViewer::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
	// Movement speed as world units per second
	const float MOVE_SPEED { 10.0f };
	const float FORWARD_MOVE_SPEED { 50.0f };
	// Rotation speed as degrees per second
	const float ROTATE_SPEED { 25.0f };
	// Mouse sensitivity as degrees per pixel
	const float MOUSE_SENSITIVITY { 0.1f};

	float timeStep{ eventData[Update::P_TIMESTEP].GetFloat() };
	auto* input { GetSubsystem<Input>() };
	
	IntVector2 mouseMove { input->GetMouseMove() };
	cameraYaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
	cameraPitch_ += MOUSE_SENSITIVITY * mouseMove.y_;

	float mouseWheelMove { static_cast<float>(input->GetMouseMoveWheel()) };
	cameraNode_->Translate(Vector3::FORWARD * FORWARD_MOVE_SPEED * timeStep * mouseWheelMove);


	if (input->GetKeyDown(KEY_Q))
		cameraRoll_ -= ROTATE_SPEED * timeStep;
	if (input->GetKeyDown(KEY_E))
		cameraRoll_ += ROTATE_SPEED * timeStep;
	cameraNode_->SetRotation(Quaternion(cameraPitch_, cameraYaw_, cameraRoll_));

	if (input->GetKeyDown(KEY_W))
		cameraNode_->Translate(Vector3::UP * MOVE_SPEED * timeStep);
	if (input->GetKeyDown(KEY_S))
		cameraNode_->Translate(Vector3::DOWN * MOVE_SPEED * timeStep);
	if (input->GetKeyDown(KEY_A))
		cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
	if (input->GetKeyDown(KEY_D))
		cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}

void GalaxyViewer::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
	int key { eventData[KeyDown::P_KEY].GetInt() };
	if (key == KEY_ESCAPE)
	{
		engine_->Exit();
	}
	if (key == KEY_X)
	{
		cameraNode_->SetPosition(Vector3(CAMERA_DEFAULT_DISTANCE, 0.0f, 0.0f));
		SetCameraLookAt(Vector3::ZERO);
	}
	if (key == KEY_Y)
	{
		cameraNode_->SetPosition(Vector3(0.0f, CAMERA_DEFAULT_DISTANCE, 0.0f));
		SetCameraLookAt(Vector3::ZERO);
	}
	if (key == KEY_Z)
	{
		cameraNode_->SetPosition(Vector3(0.0f, 0.0f, CAMERA_DEFAULT_DISTANCE));
		SetCameraLookAt(Vector3::ZERO);
	}
	if (key == KEY_O)
	{
		isCameraOrtho = !isCameraOrtho;
		cameraNode_->GetComponent<Camera>()->SetOrthographic(isCameraOrtho);
	}
	if (key == KEY_R)
	{
		RegenerateGalaxy_();
	}
}

void GalaxyViewer::CreateScene_()
{
	scene_ = new Scene(context_);
	scene_->CreateComponent<Octree>();
	GetSubsystem<Renderer>()->DrawDebugGeometry(true);

	// Bounding box of size one
	AddObject_(Vector3(-1.0f, -1.0f, 1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));
	AddObject_(Vector3(-1.0f, -1.0f, -1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));
	AddObject_(Vector3(-1.0f, 1.0f, 1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));
	AddObject_(Vector3(-1.0f, 1.0f, -1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));
	AddObject_(Vector3(1.0f, -1.0f, 1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));
	AddObject_(Vector3(1.0f, -1.0f, -1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));
	AddObject_(Vector3(1.0f, 1.0f, 1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));
	AddObject_(Vector3(1.0f, 1.0f, -1.0f), SPHERE_SCALE * 8, String("Materials/GreenTransparent.xml"));

	AddDirectionalLight(Vector3(-1.0f, 0.0f, 0.0f));
	AddDirectionalLight(Vector3(0.0f, -1.0f, 0.0f));
	AddDirectionalLight(Vector3(0.0f, 0.0f, -1.0f));
	AddDirectionalLight(Vector3(1.0f, 0.0f, 0.0f));
	AddDirectionalLight(Vector3(0.0f, 1.0f, 0.0f));
	AddDirectionalLight(Vector3(0.0f, 0.0f, 1.0f));

	cameraNode_ = scene_->CreateChild("Camera");
	cameraNode_->CreateComponent<Camera>();
	cameraNode_->SetPosition(Vector3(CAMERA_DEFAULT_DISTANCE, CAMERA_DEFAULT_DISTANCE, -CAMERA_DEFAULT_DISTANCE));
	SetCameraLookAt(Vector3::ZERO);

	auto* renderer{ GetSubsystem<Renderer>() };
	SharedPtr<Viewport> viewport{ new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()) };
	renderer->SetViewport(0, viewport);
}

void GalaxyViewer::RegenerateGalaxy_()
{
	PODVector<Node*> stars;
	scene_->GetNodesWithTag(stars, "Star");
	for (auto star : stars)
	{
		star->Remove();
	}

	GalGen::GalaxyGenerator galaxyGenerator;

	//std::vector<GalGen::Vector3> galaxy{galaxyGenerator.generateRegularSpiralGalaxy() };
	std::vector<GalGen::Vector3> galaxy{galaxyGenerator.generateToonSpiralGalaxy() };

	Node* star;
	for (auto pos : galaxy)
	{
		star = AddObject_(Vector3((float)pos.x, (float)pos.y, (float)pos.z), SPHERE_SCALE, String("Materials/StoneTiled.xml"));
		star->AddTag("Star");
	}
}

void GalaxyViewer::SetCameraLookAt(const Vector3& v)
{
	cameraNode_->LookAt(v);
	Vector3 rot { cameraNode_->GetRotation().EulerAngles() };
	cameraPitch_ = rot.x_;
	cameraYaw_ = rot.y_;
	cameraRoll_ = rot.z_;
}
void GalaxyViewer::AddDirectionalLight(const Vector3& direction)
{
	auto* lightNode { scene_->CreateChild("DirectionalLight") };
	lightNode->SetDirection(direction);
	auto* light { lightNode->CreateComponent<Light>() };
	light->SetLightType(LIGHT_DIRECTIONAL);
}

Node* GalaxyViewer::AddObject_(const Vector3& position, float size, const String& material)
{
	auto* cache { GetSubsystem<ResourceCache>() };
	auto* sphereNode { scene_->CreateChild("Object") };
	sphereNode->SetPosition(position);
	sphereNode->SetScale(Vector3(size, size, size));
	auto* sphereObject { sphereNode->CreateComponent<StaticModel>() };
	sphereObject->SetModel(cache->GetResource<Model>("Models/Pyramid.mdl"));
	sphereObject->SetMaterial(cache->GetResource<Material>(material));

	return sphereNode;
}