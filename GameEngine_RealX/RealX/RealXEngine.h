#ifndef REALX_ENGINE
#define REALX_ENGINE

#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"
#include "RealXEngineCoreData.h"

#include "../GUI/imgui.h"
#include "../GUI/imgui_impl_opengl3.h"
#include "../GUI/imgui_impl_glfw.h"
#include "../GUI/ImGuizmo.h"
#include "../Graphics/Model.h"
#include "../Graphics/GraphicsEngine.h"
#include "../Audio/AudioEngine.h"

class Scene
{
	const std::string PATH_TO_MAIN_VERTEX_SHADER = "Shaders\\shader.vert";	    // Path to vertex shader.
	const std::string PATH_TO_MAIN_FRAGMENT_SHADER = "Shaders\\shader.frag";	// Path to fragment shader.

	const std::string PATH_TO_SKYBOX_VERTEX_SHADER = "Shaders\\skybox.vert";	// Path to skybox vertex shader.
	const std::string PATH_TO_SKYBOX_FRAGMENT_SHADER = "Shaders\\skybox.frag";  // Path to skybox fragment shader.

	Camera* m_pMainCamera;			    // Camera pointer.
	EntityComponentSystem* m_pCoordinator;	    // Management for systems and components.
	Shader* m_pMainShader;			    // Main shader.
	Shader* m_pSkyboxShader;		    // Skybox shader.
	std::vector<REntity*>  m_Entities;  // All entities in the scene.
	std::vector<std::string>* m_pLogs;  // Logs info.
	
	PhysicsEngine m_PhysicsEngine;						// PhysX system.
	GraphicsEngine* m_pGraphicsEngine;			// Graphics Engine.
	AudioEngine* m_pAudioEngine;				// Audio Engine.

	std::shared_ptr<PhysicsSystem>	 m_pPhysicsSystem;							 // Physics system.
	std::shared_ptr<ModelRenderingSystem> m_pModelRenderingSystem;				 // Model rendering system.
	std::shared_ptr<MeshRenderingSystem> m_pMeshRenderingSystem;				 // Mesh rendering system.
	std::shared_ptr<CameraSystem>	 m_pCameraSystem;							 // Camera system.
	std::shared_ptr<SkyboxRenderingSystem> m_pSkyboxRenderingSystem;			 // Skybox system.
	std::shared_ptr<DirectionalLightSystem> m_pDirectionalLightSystem;			 // Direcitonal light system.
	std::shared_ptr<PointLightSystem> m_pPointLightSystem;						 // Point light system.
	std::shared_ptr<SpotLightSystem>  m_pSpotLightSystem;						 // Spot light system.
	std::shared_ptr<Audio3DSystem>	  m_pAudio3DSystem;							 // Audio 3D system.
	std::shared_ptr<PhysicsDynamicBox3DSystem> m_pPhysXDynamicBox3DSystem;		 // PhysX that handles 3D dynamic Boxes.
	std::shared_ptr<PhysicsStaticBox3DSystem> m_pPhysXStaticBox3DSystem;			 // PhysX that handles 3D static boxes.
	std::shared_ptr<PhysicsDynamicSphere3DSystem> m_pPhysXDynamicSphere3DSystem;	 // PhysX that handles 3D dynamic spheres.
	std::shared_ptr<PhysicsStaticSphere3DSystem> m_pPhysXStaticSphere3DSystem;	 // PhysX that handles 3D static spheres.
	std::shared_ptr<PhysicsDynamicCapsule3DSystem> m_pPhysXDynamicCapsule3DSystem; // PhysX that handles 3D dynamic capsules.
	std::shared_ptr<PhysicsStaticCapsule3DSystem> m_pPhysXStaticCapsule3DSystem;	 // PhysX that handles 3D static capsules.
	std::shared_ptr<PhysicsDynamicMesh3DSystem> m_pPhysXDynamicMesh3DSystem;		 // PhysX that handles 3D dynamic triangle meshes.
	std::shared_ptr<PhysicsStaticMesh3DSystem> m_pPhysXStaticMesh3DSystem;		 // PhysX that hanldes 3D static triangle meshes.
	
public:
	// Getting pointer to camera.
	Camera* getCamera()
	{
		return m_pMainCamera;
	}

	// Getting pointer to coordinator.
	EntityComponentSystem* getCoordinator()
	{
		return m_pCoordinator;
	}

	// Getting pointer to shader.
	Shader* getShader()
	{
		return m_pMainShader;
	}

	// Getting reference to the all entities.
	std::vector<REntity*>& getEntities()
	{
		return m_Entities;
	}

	// Getting reference to the all generated logs.
	std::vector<std::string>& getLogs()
	{
		return *m_pLogs;
	}

	// Default constructor.
	Scene()
	{
		// Creating and allocating the coordinator on the heap.
		m_pCoordinator = new EntityComponentSystem();

		// Creating and allocating main shader on the heap.
		m_pMainShader = new Shader();

		// Creating and allocatiing skybox shader on the heap.
		m_pSkyboxShader = new Shader();

		// Creating and allocating Logs vector on the heap.
		m_pLogs = new std::vector<std::string>();

		m_pGraphicsEngine = new GraphicsEngine();
		m_pAudioEngine = new AudioEngine();
	}

	// Creating entity.
	REntity* CreateEntity()
	{
		REntity* newEntity = new REntity(m_pCoordinator);
		m_Entities.push_back(newEntity);
		return newEntity;
	}

	// Initializing the engine.
	void Init()
	{
		// Initializing the PhysX.
		m_PhysicsEngine.InitEssentialVariables();
		m_PhysicsEngine.InitScene();
		m_PhysicsEngine.SetScenePVDClient();

		// Initializing the main coordinator for ECS (ENTITY-COMPONENT-SYSTEM).
		m_pCoordinator->Init();

		// Initializing main shader.
		m_pMainShader->CreateFromFiles(PATH_TO_MAIN_VERTEX_SHADER, PATH_TO_MAIN_FRAGMENT_SHADER);

		// Initializing skybox shader.
		m_pSkyboxShader->CreateFromFiles(PATH_TO_SKYBOX_VERTEX_SHADER, PATH_TO_SKYBOX_FRAGMENT_SHADER);

		// Registering Components that can be used in by Entities.
		m_pCoordinator->Init();
		m_pCoordinator->RegisterComponent<GravityComponent>();
		m_pCoordinator->RegisterComponent<RigidBodyComponent>();
		m_pCoordinator->RegisterComponent<TransformComponent>();
		m_pCoordinator->RegisterComponent<ModelRendererComponent>();
		m_pCoordinator->RegisterComponent<CameraComponent>();
		m_pCoordinator->RegisterComponent<MeshRendererComponent>();
		m_pCoordinator->RegisterComponent<SkyboxComponent>();
		m_pCoordinator->RegisterComponent<DirectionalLightComponent>();
		m_pCoordinator->RegisterComponent<MaterialComponent>();
		m_pCoordinator->RegisterComponent<PointLightComponent>();
		m_pCoordinator->RegisterComponent<SpotLightComponent>();
		m_pCoordinator->RegisterComponent<TagComponent>();
		m_pCoordinator->RegisterComponent<Audio3DComponent>();

		m_pCoordinator->RegisterComponent<PhysXDynamicBox3DComponent>();
		m_pCoordinator->RegisterComponent<PhysXStaticBox3DComponent>();

		m_pCoordinator->RegisterComponent<PhysXDynamicSphere3DComponent>();
		m_pCoordinator->RegisterComponent<PhysXStaticSphere3DComponent>();

		m_pCoordinator->RegisterComponent<PhysXDynamicCapsule3DComponent>();
		m_pCoordinator->RegisterComponent<PhysXStaticCapsule3DComponent>();

		m_pCoordinator->RegisterComponent<PhysXDynamicMesh3DComponent>();
		m_pCoordinator->RegisterComponent<PhysXStaticMesh3DComponent>();

		// Registering systems that will use entities with special signature (combination of components).
		m_pPhysicsSystem = m_pCoordinator->RegisterSystem<PhysicsSystem>();
		m_pModelRenderingSystem = m_pCoordinator->RegisterSystem<ModelRenderingSystem>();
		m_pCameraSystem = m_pCoordinator->RegisterSystem<CameraSystem>();
		m_pMeshRenderingSystem = m_pCoordinator->RegisterSystem<MeshRenderingSystem>();
		m_pSkyboxRenderingSystem = m_pCoordinator->RegisterSystem<SkyboxRenderingSystem>();
		m_pDirectionalLightSystem = m_pCoordinator->RegisterSystem<DirectionalLightSystem>();
		m_pPointLightSystem = m_pCoordinator->RegisterSystem<PointLightSystem>();
		m_pSpotLightSystem = m_pCoordinator->RegisterSystem<SpotLightSystem>();
		m_pAudio3DSystem = m_pCoordinator->RegisterSystem<Audio3DSystem>();

		m_pPhysXDynamicBox3DSystem = m_pCoordinator->RegisterSystem<PhysicsDynamicBox3DSystem>();
		m_pPhysXStaticBox3DSystem = m_pCoordinator->RegisterSystem<PhysicsStaticBox3DSystem>();

		m_pPhysXDynamicSphere3DSystem = m_pCoordinator->RegisterSystem<PhysicsDynamicSphere3DSystem>();
		m_pPhysXStaticSphere3DSystem = m_pCoordinator->RegisterSystem<PhysicsStaticSphere3DSystem>();

		m_pPhysXDynamicCapsule3DSystem = m_pCoordinator->RegisterSystem<PhysicsDynamicCapsule3DSystem>();
		m_pPhysXStaticCapsule3DSystem = m_pCoordinator->RegisterSystem<PhysicsStaticCapsule3DSystem>();

		m_pPhysXDynamicMesh3DSystem = m_pCoordinator->RegisterSystem<PhysicsDynamicMesh3DSystem>();
		m_pPhysXStaticMesh3DSystem = m_pCoordinator->RegisterSystem<PhysicsStaticMesh3DSystem>();

		// Creating and setting up signature for physics system.
		Signature physicsSignature;
		physicsSignature.set(m_pCoordinator->GetComponentType<GravityComponent>());
		physicsSignature.set(m_pCoordinator->GetComponentType<RigidBodyComponent>());
		physicsSignature.set(m_pCoordinator->GetComponentType<TransformComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsSystem>(physicsSignature);

		// Creating and setting up a signature for rendering system.
		Signature modelRenderingSignature;
		modelRenderingSignature.set(m_pCoordinator->GetComponentType<ModelRendererComponent>());
		modelRenderingSignature.set(m_pCoordinator->GetComponentType<MaterialComponent>());
		m_pCoordinator->SetSystemSignature<ModelRenderingSystem>(modelRenderingSignature);

		// Creating and setting up a signature for mesh rendering system.
		Signature meshRenderingSignature;
		meshRenderingSignature.set(m_pCoordinator->GetComponentType<MeshRendererComponent>());
		meshRenderingSignature.set(m_pCoordinator->GetComponentType<MaterialComponent>());
		m_pCoordinator->SetSystemSignature<MeshRenderingSystem>(meshRenderingSignature);

		// Creating and setting up a siganture for camera system.
		Signature cameraSignature;
		cameraSignature.set(m_pCoordinator->GetComponentType<CameraComponent>());
		m_pCoordinator->SetSystemSignature<CameraSystem>(cameraSignature);

		// Creating and setting up a signature for skybox rendering system.
		Signature skyboxSignature;
		skyboxSignature.set(m_pCoordinator->GetComponentType<SkyboxComponent>());
		m_pCoordinator->SetSystemSignature<SkyboxRenderingSystem>(skyboxSignature);

		// Creating and setting up a signature for directional light system.
		Signature directionalLightSignature;
		directionalLightSignature.set(m_pCoordinator->GetComponentType<DirectionalLightComponent>());
		m_pCoordinator->SetSystemSignature<DirectionalLightSystem>(directionalLightSignature);

		// Creating and setting up a signature for point light system.
		Signature pointLightSignature;
		pointLightSignature.set(m_pCoordinator->GetComponentType<PointLightComponent>());
		m_pCoordinator->SetSystemSignature<PointLightSystem>(pointLightSignature);

		// Creating and setting up a signature for spot light system.
		Signature spotLightSignature;
		spotLightSignature.set(m_pCoordinator->GetComponentType<SpotLightComponent>());
		m_pCoordinator->SetSystemSignature<SpotLightSystem>(spotLightSignature);

		// Creating and setting up a signature for audio 3d system.
		Signature audio3DSystemSignature;
		audio3DSystemSignature.set(m_pCoordinator->GetComponentType<Audio3DComponent>());
		m_pCoordinator->SetSystemSignature<Audio3DSystem>(audio3DSystemSignature);

		// Creating and setting up a signature for PhysX3DBox System.
		Signature physXDynamicBox3DSystemSignature;
		physXDynamicBox3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXDynamicBox3DComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsDynamicBox3DSystem>(physXDynamicBox3DSystemSignature);

		// Creating and setting up a signature for PhysX3DBox System.
		Signature physXStaticBox3DSystemSignature;
		physXStaticBox3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXStaticBox3DComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsStaticBox3DSystem>(physXStaticBox3DSystemSignature);

		// Creating and setting up a signature for PhysXDynamicSphere3D System.
		Signature physXDynamicSphere3DSystemSignature;
		physXDynamicSphere3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXDynamicSphere3DComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsDynamicSphere3DSystem>(physXDynamicSphere3DSystemSignature);

		// Creating and setting up a signature for PhysXStaticSphere3D System.
		Signature physXStaticSphere3DSystemSignature;
		physXStaticSphere3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXStaticSphere3DComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsStaticSphere3DSystem>(physXStaticSphere3DSystemSignature);

		// Creating and setting up a signature for PhysXDynamicCapsule3D System.
		Signature physXDynamicCapsule3DSystemSignature;
		physXDynamicCapsule3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXDynamicCapsule3DComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsDynamicCapsule3DSystem>(physXDynamicCapsule3DSystemSignature);

		// Creating and setting up a signature for PhysXStaticCapsule3D System.
		Signature physXStaticCapsule3DSystemSignature;
		physXStaticCapsule3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXStaticCapsule3DComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsStaticCapsule3DSystem>(physXStaticCapsule3DSystemSignature);

		// Creating and setting up a signature for PhysXDynamicMesh3D System.
		Signature physXDynamicMesh3DSystemSignature;
		physXDynamicMesh3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXDynamicMesh3DComponent>());
		physXDynamicMesh3DSystemSignature.set(m_pCoordinator->GetComponentType<ModelRendererComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsDynamicMesh3DSystem>(physXDynamicMesh3DSystemSignature);

		// Creating and setting up a signature for PhysXStaticMesh3D System.
		Signature physXStaticMesh3DSystemSignature;
		physXStaticMesh3DSystemSignature.set(m_pCoordinator->GetComponentType<PhysXStaticMesh3DComponent>());
		physXStaticMesh3DSystemSignature.set(m_pCoordinator->GetComponentType<ModelRendererComponent>());
		m_pCoordinator->SetSystemSignature<PhysicsStaticMesh3DSystem>(physXStaticMesh3DSystemSignature);
	}

	// Clearing the previous scene (meshes, entities, etc.).
	void ClearPreviousScene(Window* pWindow)
	{
		// Clearing color attachment.
		pWindow->ClearColorBuffer();

		// Clearing depth attachment.
		pWindow->ClearDepthBuffer();
	}

	// Updating the scene like physics.
	void UpdateScene(float dt, Window* pWindow)
	{
		// PHYSX ===============================================================

		// Updating PhysX dynamic Box3D System.
		m_pPhysXDynamicBox3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX static Box3D system.
		m_pPhysXStaticBox3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX dynamic Sphere3D system.
		m_pPhysXDynamicSphere3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX static Sphere3D system.
		m_pPhysXStaticSphere3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX dynamic Capsule3D system.
		m_pPhysXDynamicCapsule3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX static Capsule3D sytem.
		m_pPhysXStaticCapsule3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX dynamic Mesh3D system.
		m_pPhysXDynamicMesh3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX static Mesh3D system.
		m_pPhysXStaticMesh3DSystem->Update(*m_pCoordinator, &m_PhysicsEngine);

		// Updating PhysX.
		m_PhysicsEngine.Update(m_PhysicsEngine.getValueOfNormalMotion());

		// ======================================================================

		// Polling for events.
		pWindow->PollEvents();

		// Updating physics system.
		m_pPhysicsSystem->Update(*m_pCoordinator, dt);

		// CAMERA ================================================================

		// Getting main camera from system.
		m_pMainCamera = m_pCameraSystem->getMainCameraFromEntitiesWithCameraComponent(*m_pCoordinator);

		// Setting up aspect ratio for main camera.
		m_pMainCamera->setAspectRatio((GLfloat)pWindow->getWitdh() / (GLfloat)pWindow->getHeight());

		// =======================================================================

		// Updating audio3D system.
		m_pAudio3DSystem->Update(m_pCoordinator, m_pAudioEngine,m_pMainCamera);
	}

	// Rendering scene like entities.
	void RenderScene(Window* pWindow)
	{
		// 1. Binding Frame buffer for texture.
		pWindow->BindToFrameBufferForTexture();

		// 2. Clearing the color attachment for frame buffer.
		pWindow->ClearColorBuffer();

		// 3. Clearing the depth attachment for frame buffer.
		pWindow->ClearDepthBuffer();

		// 4. Enabling Depth testing.
		pWindow->EnableDepthTest();

		// =================== SYSTEMS RENDERING ====================

		// 5. Updating skybox rendering system -> Settup up a cubemap and disabling/ enabling Depth Mask.
		m_pSkyboxRenderingSystem->Update(pWindow, m_pGraphicsEngine, m_pCoordinator, m_pSkyboxShader, m_pMainCamera);

		// 6. Start using main program.
		m_pMainShader->UseProgram();

			// 7. Setting up main camera.
			m_pMainShader->setCamera("camera", m_pMainCamera);

			// 8. Setting up directional lights in the shader program.
			m_pDirectionalLightSystem->Update(m_pCoordinator, m_pMainShader);

			// 9. Setting up point lights in the shader program.
			m_pPointLightSystem->Update(m_pCoordinator, m_pMainShader);

			// 10. Setting up spot lights in the shader program.
			m_pSpotLightSystem->Update(m_pCoordinator, m_pMainShader);

			// 11. Updating model rendering system -> Setting up a texture of scene (in Window) by rendering frame buffer into it.
			m_pModelRenderingSystem->Update(m_pCoordinator, m_pGraphicsEngine, m_pMainShader);

			// 12. Updating mesh rendering system -> Settup up a texture and meshes.
			m_pMeshRenderingSystem->Update(m_pCoordinator, m_pGraphicsEngine, m_pMainShader);

		// 13. Stop using program.
		m_pMainShader->StopUsingProgram();

		// ==========================================================

		// 14. Unbiding frame buffer for texture.
		pWindow->UseDefaultFrameBuffer();

		// 15. Swapping color buffer.
		pWindow->SwapBuffers();
	}

	// Setting defaule example scene.
	void SetUpExampleScene()
	{
		// Backpack entity:
		REntity* backPackEntity = CreateEntity();
		backPackEntity->AddComponent(ModelRendererComponent{ "Models\\Backpack.obj" });
		backPackEntity->AddComponent(MaterialComponent{});
		strncpy_s(backPackEntity->GetComponent<TagComponent>().name, "Backpack entity", 30);
		backPackEntity->AddComponent(PhysXDynamicBox3DComponent{});

		// Skull entity:
		REntity* skullEntity = CreateEntity();
		skullEntity->AddComponent(ModelRendererComponent{ "Models\\Skull.obj" });
		skullEntity->AddComponent(MaterialComponent{});
		skullEntity->GetComponent<TransformComponent>().position = glm::vec3(2.5f, 0.0f, 0.0f);
		strncpy_s(skullEntity->GetComponent<TagComponent>().name, "Skull entity", 30);
		skullEntity->AddComponent(PhysXDynamicSphere3DComponent{});

		// Apple entity.
		REntity* appleEntity = CreateEntity();
		appleEntity->AddComponent(ModelRendererComponent{ "Models\\apple.obj" });
		appleEntity->AddComponent(MaterialComponent{});
		appleEntity->GetComponent<TransformComponent>().position = glm::vec3(-2.5f, 0.0f, 0.0f);
		strncpy_s(appleEntity->GetComponent<TagComponent>().name, "Apple entity", 30);
		appleEntity->AddComponent(PhysXDynamicCapsule3DComponent{});

		// Floor entity:
		REntity* floorEntity = CreateEntity();
		floorEntity->AddComponent(MeshRendererComponent{});
		floorEntity->AddComponent(MaterialComponent{});
		auto& refMeshRendererComponent = floorEntity->GetComponent<MeshRendererComponent>();
		strncpy_s(refMeshRendererComponent.meshType, "Rectangle", 10);
		strncpy_s(refMeshRendererComponent.pathToTexture, "Textures\\container.jpg", 23);
		auto& refTransform = floorEntity->GetComponent<TransformComponent>();
		refTransform.position.y = -2.5f;
		refTransform.rotation.x = 1.58f;
		refTransform.scale.x = 10.0f;
		refTransform.scale.y = 10.0f;
		strncpy_s(floorEntity->GetComponent<TagComponent>().name, "Floor entity", 30);
		floorEntity->AddComponent(PhysXStaticBox3DComponent{});

		// Camera entity:
		REntity* cameraEntity = CreateEntity();
		cameraEntity->AddComponent(CameraComponent{ Camera(), true });
		cameraEntity->GetComponent<CameraComponent>().camera.getRefPosition()->z = 10;
		strncpy_s(cameraEntity->GetComponent<TagComponent>().name, "Camera entity", 30);

		// Skybox entity:
		REntity* skyboxEntity = CreateEntity();
		skyboxEntity->AddComponent(SkyboxComponent{});
		strncpy_s(skyboxEntity->GetComponent<TagComponent>().name, "Skybox entity", 30);

		// Directional light entity:
		REntity* directionalLightEntity = CreateEntity();
		directionalLightEntity->AddComponent(DirectionalLightComponent{});
		strncpy_s(directionalLightEntity->GetComponent<TagComponent>().name, "Directional light entity", 30);

		// Point light entity:
		REntity* pointLightEntity = CreateEntity();
		pointLightEntity->AddComponent(PointLightComponent{});
		strncpy_s(pointLightEntity->GetComponent<TagComponent>().name, "Point light entity", 30);

		// Spot light entity:
		REntity* spotLightEntity = CreateEntity();
		spotLightEntity->AddComponent(SpotLightComponent{});
		strncpy_s(spotLightEntity->GetComponent<TagComponent>().name, "Spot light entity", 30);

		// Audio entity:
		REntity* audio3DEntity = CreateEntity();
		audio3DEntity->AddComponent(Audio3DComponent{});
		strncpy_s(audio3DEntity->GetComponent<TagComponent>().name, "Audio3D entity", 30);
	}
};

class GUI
{
private:
	REntity* m_pCurrentlySelectedEntity = nullptr;	// Pointer to the currently selected entity.

public:

	// Setting up current entity.
	void SetCurrentEntity(REntity* pCurrentEntity)
	{
		m_pCurrentlySelectedEntity = pCurrentEntity;
	}

	// Initializing GUI.
	void Init(Window* pWindow)
	{
		// Creating context and getting IO.
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };

		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.38f, 0.38f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.28f, 0.28f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };

		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setting up platform/ renderer bindings.
		ImGui_ImplGlfw_InitForOpenGL(pWindow->getGLFWwindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}

	// Updating GUI.
	void Update(Window* pWindow, Scene* pScene)
	{
		// Creating a new frame.
		NewFrame();

		// Rendering window with entities.
		RenderEntitiesManager(pScene->getEntities(), *pScene->getCoordinator());

		// Render inspector widget.
		RenderInspectorWidgetForCurrentEntity();

		// Rendering logs.
		RenderLogs(pScene->getLogs());

		// Rendering game window.
		RenderScene(pWindow->getTextureColorFromFrameBuffer(), pScene->getEntities(), *pScene->getCamera());
	}

	// Rendering GUI.
	void Render()
	{
		// Rendering the scene.
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	// Disposing GUI.
	void Shutdown()
	{
		// Freeing resources.
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

private:

	// Rendering logs.
	void RenderLogs(const std::vector<std::string>& logs)
	{
		ImGui::Begin("Logs");
		{
			ImGui::BeginChild("Scrolling");
			for (int i = 0; i < logs.size(); i++)
			{
				ImGui::Text(logs[i].c_str(), i);
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}

	// Rendering inspector widget for current entity.
	void RenderInspectorWidgetForCurrentEntity()
	{
		ImGui::Begin("Inspector");

		// Formats of displaying data.
		float min = -20.0f, max = 20.0f, step = 0.01f; char format[] = "%.2f"; bool a = false, b = false, c = false;

		// Displaying components of current entity.
		if (m_pCurrentlySelectedEntity != nullptr)
		{
			// CAMERA ===========================================================
			if (m_pCurrentlySelectedEntity->HasComponent<CameraComponent>())
			{
				if (ImGui::CollapsingHeader("Camera component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					CameraComponent& refCameraComponent = m_pCurrentlySelectedEntity->GetComponent<CameraComponent>();
					ImGui::DragFloat3("Position", (float*)refCameraComponent.camera.getRefPosition(), step, min, max, format, 0);
					ImGui::DragFloat("Yaw angle", &refCameraComponent.camera.getRefYawAngle(), step, min, max, format, 0);
					ImGui::DragFloat("Pitch angle", &refCameraComponent.camera.getRefPitchAngle(), step, min, max, format, 0);
				}
				ImGui::Text("");
			}

			// TAG ==============================================================
			if (m_pCurrentlySelectedEntity->HasComponent<TagComponent>())
			{
				if (ImGui::CollapsingHeader("Tag component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					TagComponent& refTagComponent = m_pCurrentlySelectedEntity->GetComponent<TagComponent>();
					ImGui::InputText("Tag", refTagComponent.name, 30);
				}
				ImGui::Text("");
			}

			// TRANSFORM ========================================================
			if (m_pCurrentlySelectedEntity->HasComponent<TransformComponent>())
			{
				if (ImGui::CollapsingHeader("Transform component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					TransformComponent& refTrasnfromComponent = m_pCurrentlySelectedEntity->GetComponent<TransformComponent>();
					ImGui::DragFloat3("Position", (float*)&refTrasnfromComponent.position, step, min, max, format, 0);
					ImGui::DragFloat3("Rotation", (float*)&refTrasnfromComponent.rotation, step, min, max, format, 0);
					ImGui::DragFloat3("Scale", (float*)&refTrasnfromComponent.scale, step, min, max, format, 0);
				}
				ImGui::Text("");
			}

			// RENDERING ========================================================
			if (m_pCurrentlySelectedEntity->HasComponent<ModelRendererComponent>())
			{
				if (ImGui::CollapsingHeader("Model renderer component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ModelRendererComponent& refModelRendererComponent = m_pCurrentlySelectedEntity->GetComponent<ModelRendererComponent>();
					ImGui::InputText("Path to model", refModelRendererComponent.pathToModel, 30);
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<MeshRendererComponent>())
			{
				if (ImGui::CollapsingHeader("Mesh renderer component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					MeshRendererComponent& refMeshRendererComponent = m_pCurrentlySelectedEntity->GetComponent<MeshRendererComponent>();
					ImGui::InputText("Mesh type", refMeshRendererComponent.meshType, 30);
					ImGui::InputText("Path to texture", refMeshRendererComponent.pathToTexture, 30);
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<MaterialComponent>())
			{
				if (ImGui::CollapsingHeader("Material component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					MaterialComponent& refMaterialComponent = m_pCurrentlySelectedEntity->GetComponent<MaterialComponent>();
					ImGui::DragFloat("Shininess", (float*)&refMaterialComponent.material.getRefShininess(), step, min, max, format, 0);
					ImGui::DragFloat("Specular intensity", (float*)&refMaterialComponent.material.getRefSpecularIntensity(), step, min, max, format, 0);
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<SkyboxComponent>())
			{
				if (ImGui::CollapsingHeader("Skybox component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					SkyboxComponent& refSkyboxComponent = m_pCurrentlySelectedEntity->GetComponent<SkyboxComponent>();
					ImGui::InputText("Path to right texture", refSkyboxComponent.pathToRightTexture, 50);
					ImGui::InputText("Path to left texture", refSkyboxComponent.pathToLeftTexture, 50);
					ImGui::InputText("Path to top texture", refSkyboxComponent.pathToTopTexture, 50);
					ImGui::InputText("Path to bottom texture", refSkyboxComponent.pathToBottomTexture, 50);
					ImGui::InputText("Path to front texture", refSkyboxComponent.pathToFrontTexture, 50);
					ImGui::InputText("Path to back texture", refSkyboxComponent.pathToBackTexture, 50);
				}
				ImGui::Text("");
			}

			// LIGHTS ===========================================================
			if (m_pCurrentlySelectedEntity->HasComponent<DirectionalLightComponent>())
			{
				if (ImGui::CollapsingHeader("Directional light component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					DirectionalLightComponent& refDirectionalLightComponent = m_pCurrentlySelectedEntity->GetComponent<DirectionalLightComponent>();
					ImGui::ColorEdit3("Color", (float*)&refDirectionalLightComponent.light.getRefColour(), ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
					ImGui::DragFloat3("Direction", (float*)&refDirectionalLightComponent.light.getRefDirection(), step, min, max, format, 0);
					ImGui::DragFloat("Ambient intensity", &refDirectionalLightComponent.light.getRefAmbientIntensity(), step, min, max, format, 0);
					ImGui::DragFloat("Diffuse intensity", &refDirectionalLightComponent.light.getRefDiffuseIntensity(), step, min, max, format, 0);
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PointLightComponent>())
			{
				if (ImGui::CollapsingHeader("Point light component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PointLightComponent& refPointLightComponent = m_pCurrentlySelectedEntity->GetComponent<PointLightComponent>();
					ImGui::ColorEdit3("Color", (float*)&refPointLightComponent.light.getRefColour(), ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
					ImGui::DragFloat3("Position", (float*)&refPointLightComponent.light.getRefPosition(), step, min, max, format, 0);
					ImGui::DragFloat("Ambient intensity", &refPointLightComponent.light.getRefAmbientIntensity(), step, min, max, format, 0);
					ImGui::DragFloat("Diffuse intensity", &refPointLightComponent.light.getRefDiffuseIntensity(), step, min, max, format, 0);
					ImGui::DragFloat("Constant factor", &refPointLightComponent.light.getRefConstantFactor(), step, min, max, format, 0);
					ImGui::DragFloat("Linear factor", &refPointLightComponent.light.getRefLinearFactor(), step, min, max, format, 0);
					ImGui::DragFloat("Exponent factor", &refPointLightComponent.light.getRefExponentFactor(), step, min, max, format, 0);
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<SpotLightComponent>())
			{
				if (ImGui::CollapsingHeader("Spot light component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					SpotLightComponent& refSpotLightComponent = m_pCurrentlySelectedEntity->GetComponent<SpotLightComponent>();
					ImGui::ColorEdit3("Color", (float*)&refSpotLightComponent.light.getRefColour(), ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
					ImGui::DragFloat3("Direction", (float*)&refSpotLightComponent.light.getRefDirection(), step, min, max, format, 0);
					ImGui::DragFloat3("Position", (float*)&refSpotLightComponent.light.getRefPosition(), step, min, max, format, 0);
					ImGui::DragFloat("Ambient intensity", &refSpotLightComponent.light.getRefAmbientIntensity(), step, min, max, format, 0);
					ImGui::DragFloat("Diffuse intensity", &refSpotLightComponent.light.getRefDiffuseIntensity(), step, min, max, format, 0);
					ImGui::DragFloat("Constant factor", &refSpotLightComponent.light.getRefConstantFactor(), step, min, max, format, 0);
					ImGui::DragFloat("Linear factor", &refSpotLightComponent.light.getRefLinearFactor(), step, min, max, format, 0);
					ImGui::DragFloat("Exponent factor", &refSpotLightComponent.light.getRefExponentFactor(), step, min, max, format, 0);
					ImGui::DragFloat("Edge", &refSpotLightComponent.light.getRefEdge(), step, min, max, format, 0);
				}
				ImGui::Text("");
			}

			// AUDIO ============================================================
			if (m_pCurrentlySelectedEntity->HasComponent<Audio3DComponent>())
			{
				if (ImGui::CollapsingHeader("Audio3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					Audio3DComponent& refAudio3DComponent = m_pCurrentlySelectedEntity->GetComponent<Audio3DComponent>();
					ImGui::InputText("Path to file", refAudio3DComponent.pathToFile, 30);
					if (ImGui::Button("Update", ImVec2(100, 50)))
					{
						refAudio3DComponent.updated = false;
					}
					ImGui::SameLine();
					if (ImGui::Button("Play", ImVec2(100, 50)))
					{
						refAudio3DComponent.Play();
					}
					ImGui::SameLine();
					if (ImGui::Button("Stop", ImVec2(100, 50)))
					{
						refAudio3DComponent.Stop();
					}
					ImGui::SameLine();
					if (ImGui::Button("Restart", ImVec2(100, 50)))
					{
						refAudio3DComponent.updated = false;
						refAudio3DComponent.Play();
					}
					ImGui::NewLine();
				}
				ImGui::Text("");
			}

			// PHYSICS ==========================================================
			if (m_pCurrentlySelectedEntity->HasComponent<RigidBodyComponent>())
			{
				if (ImGui::CollapsingHeader("Rigidbody component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					RigidBodyComponent& refRigidBody = m_pCurrentlySelectedEntity->GetComponent<RigidBodyComponent>();
					ImGui::DragFloat3("Velocity", (float*)&refRigidBody.velocity, step, min, max, format, 0);
					ImGui::DragFloat3("Acceleration", (float*)&refRigidBody.acceleration, step, min, max, format, 0);
				}
				ImGui::Text("");
			}

			// PHYSX ============================================================
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicBox3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Dynamic Box3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PhysXDynamicBox3DComponent& refPhysXBox3DComponent = m_pCurrentlySelectedEntity->GetComponent<PhysXDynamicBox3DComponent>();
					ImGui::Text("Mass: %f", refPhysXBox3DComponent.mass);
					static glm::vec3 force(0.0f, 0.0f, 0.0f);
					ImGui::DragFloat3("Force", (float*)&force, step, min, max, format, 0);
					if (ImGui::Button("Add force", ImVec2(100, 50)))
					{
						refPhysXBox3DComponent.physXRigidBody->addForce(physx::PxVec3(force.x, force.y, force.z));
					}
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXStaticBox3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Static Box3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{

				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicSphere3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Dynamic Sphere3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PhysXDynamicSphere3DComponent& refPhysXSphere3DComponent = m_pCurrentlySelectedEntity->GetComponent<PhysXDynamicSphere3DComponent>();
					ImGui::Text("Mass: %f", refPhysXSphere3DComponent.mass);
					ImGui::Text("Radius: %f", refPhysXSphere3DComponent.radius);
					static glm::vec3 sForce(0.0f, 0.0f, 0.0f);
					ImGui::DragFloat3("Sphere Force", (float*)&sForce, step, min, max, format, 0);
					if (ImGui::Button("Add force", ImVec2(100, 50)))
					{
						refPhysXSphere3DComponent.physXRigidBody->addForce(physx::PxVec3(sForce.x, sForce.y, sForce.z));
					}
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXStaticSphere3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Static Sphere3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PhysXStaticSphere3DComponent& refPhysXSphere3DComponent = m_pCurrentlySelectedEntity->GetComponent<PhysXStaticSphere3DComponent>();
					ImGui::Text("Radius: %f", refPhysXSphere3DComponent.radius);
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicCapsule3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Dynamic Capsule3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PhysXDynamicCapsule3DComponent& refPhysXCapsule3DComponent = m_pCurrentlySelectedEntity->GetComponent<PhysXDynamicCapsule3DComponent>();
					ImGui::Text("Mass: %f", refPhysXCapsule3DComponent.mass);
					ImGui::Text("Radius: %f", refPhysXCapsule3DComponent.radius);
					ImGui::Text("Half height: %f", refPhysXCapsule3DComponent.halfHeight);
					static glm::vec3 cForce(0.0f, 0.0f, 0.0f);
					ImGui::DragFloat3("Capsule force", (float*)&cForce, step, min, max, format, 0);
					if (ImGui::Button("Add force", ImVec2(100, 50)))
					{
						refPhysXCapsule3DComponent.physXRigidBody->addForce(physx::PxVec3(cForce.x, cForce.y, cForce.z));
					}
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXStaticCapsule3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Static Capsule3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PhysXStaticCapsule3DComponent& refPhysXCapsule3DComponent = m_pCurrentlySelectedEntity->GetComponent<PhysXStaticCapsule3DComponent>();
					ImGui::Text("Radius: %f", refPhysXCapsule3DComponent.radius);
					ImGui::Text("Half height: %f", refPhysXCapsule3DComponent.halfHeight);
				}
				ImGui::Text("");
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicMesh3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Dynamic Mesh3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PhysXDynamicMesh3DComponent& refPhysXMesh3DComponent = m_pCurrentlySelectedEntity->GetComponent<PhysXDynamicMesh3DComponent>();
					ImGui::Text("Mass: %f", refPhysXMesh3DComponent.mass);
					static glm::vec3 mForce(0.0f, 0.0f, 0.0f);
					ImGui::DragFloat3("Mesh force", (float*)&mForce, step, min, max, format, 0);
					if (ImGui::Button("Add force", ImVec2(100, 50)))
					{
						refPhysXMesh3DComponent.physXRigidBody->addForce(physx::PxVec3(mForce.x, mForce.y, mForce.z));
					}
					ImGui::Text("");
				}
			}
			if (m_pCurrentlySelectedEntity->HasComponent<PhysXStaticMesh3DComponent>())
			{
				if (ImGui::CollapsingHeader("PhysX Static Mesh3D component", ImGuiTreeNodeFlags_DefaultOpen))
				{
					PhysXStaticMesh3DComponent& refPhysXMesh3DComponent = m_pCurrentlySelectedEntity->GetComponent<PhysXStaticMesh3DComponent>();
				}
				ImGui::Text("");
			}

			// Adding components to the current entity.
			if (ImGui::BeginMenu("Add component"))
			{
				// RENDERING ===================================
				if (ImGui::MenuItem("Model Renderer component", NULL, &a))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<ModelRendererComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(ModelRendererComponent{ "Models\\backpack.obj" });
						m_pCurrentlySelectedEntity->AddComponent(MaterialComponent{});
					}
				}
				if (ImGui::MenuItem("Mesh Renderer component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<MeshRendererComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(MeshRendererComponent{});
						m_pCurrentlySelectedEntity->AddComponent(MaterialComponent{});
					}
				}
				// SKYBOX =======================================
				if (ImGui::MenuItem("Skybox component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<SkyboxComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(SkyboxComponent{});
					}
				}
				// CAMERA ========================================
				if (ImGui::MenuItem("Camera component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<CameraComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(CameraComponent{});
					}
				}
				// LIGHTS =========================================
				if (ImGui::MenuItem("Directional light component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<DirectionalLightComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(DirectionalLightComponent{});
					}
				}
				if (ImGui::MenuItem("Point light component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PointLightComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PointLightComponent{});
					}
				}
				if (ImGui::MenuItem("Spot light component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<SpotLightComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(SpotLightComponent{});
					}
				}
				// AUDIO ======================================
				if (ImGui::MenuItem("Audio3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<Audio3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(Audio3DComponent{});
					}
				}

				// PHYSX ======================================
				if (ImGui::MenuItem("PhysX Dynamic Box3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicBox3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXDynamicBox3DComponent{});
					}
				}
				if (ImGui::MenuItem("PhysX Static Box3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXStaticBox3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXStaticBox3DComponent{});
					}
				}
				if (ImGui::MenuItem("PhysX Dynamic Sphere3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicSphere3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXDynamicSphere3DComponent{});
					}
				}
				if (ImGui::MenuItem("PhysX Static Sphere3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXStaticSphere3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXStaticSphere3DComponent{});
					}
				}
				if (ImGui::MenuItem("PhysX Dynamic Capsule3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicCapsule3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXDynamicCapsule3DComponent{});
					}
				}
				if (ImGui::MenuItem("PhysX Static Capsule3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXStaticCapsule3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXStaticCapsule3DComponent{});
					}
				}
				if (ImGui::MenuItem("PhysX Dynamic Mesh3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXDynamicMesh3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXDynamicMesh3DComponent{});
					}
				}
				if (ImGui::MenuItem("PhysX Static Mesh3D component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<PhysXStaticMesh3DComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(PhysXStaticMesh3DComponent{});
					}
				}

				// PHYSYICS ======================================
				if (ImGui::MenuItem("RigidBody component", NULL, &b))
				{
					if (!m_pCurrentlySelectedEntity->HasComponent<RigidBodyComponent>())
					{
						m_pCurrentlySelectedEntity->AddComponent(RigidBodyComponent{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f) });
						m_pCurrentlySelectedEntity->AddComponent(GravityComponent{ glm::vec3(0.0f, -9.81f, 0.0f) });
					}
				}
				ImGui::EndMenu();
			}
		}

		ImGui::End();
	}

	// Rendering scene.
	void RenderScene(GLuint textureID, std::vector<REntity*>& entities, Camera& camera)
	{
		ImGui::Begin("Scene");
		{
			ImGui::BeginChild("Scene");
			ImVec2 wsize = ImGui::GetWindowSize();
			ImGui::Image((ImTextureID)textureID, wsize, ImVec2(0, 1), ImVec2(1, 0));
			RenderGuizmo(entities, camera);
			ImGui::EndChild();
		}
		ImGui::End();
	}

	// Rendering entities manager.
	void RenderEntitiesManager(std::vector<REntity*>& entities, EntityComponentSystem& coordinator)
	{
		ImGui::Begin("Entities:");

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Number of entities: %d", entities.size());

		for (int i = 0; i < entities.size(); i++)
		{
			REntity* entity = entities[i];

			std::string tag = entity->GetComponent<TagComponent>().name;

			ImGuiTreeNodeFlags flags = (entity->getID() == m_pCurrentlySelectedEntity->getID() ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)(uint64_t)entity->getID(), flags, tag.c_str());

			if (ImGui::IsItemClicked())
			{
				m_pCurrentlySelectedEntity = entity;
			}

			if (opened)
			{
				ImGui::TreePop();
			}
		}

		ImGui::Text("");
		ImGui::Text("Add entity: ");
		if (ImGui::Button("Add", ImVec2(100, 50)))
		{
			REntity* newEntity = new REntity(&coordinator);
			entities.push_back(newEntity);
		}

		ImGui::End();
	}

	// Rendering guizmo.
	void RenderGuizmo(std::vector<REntity*>& entities, Camera& camera)
	{
		static ImGuizmo::OPERATION operation(ImGuizmo::OPERATION::TRANSLATE);

		if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_T))
		{
			operation = ImGuizmo::OPERATION::TRANSLATE;
		}
		else if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_R))
		{
			operation = ImGuizmo::OPERATION::ROTATE;
		}
		else if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_S))
		{
			operation = ImGuizmo::OPERATION::SCALE;
		}

		if (m_pCurrentlySelectedEntity != nullptr)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			glm::mat4 cameraView = camera.getViewMatrix();
			glm::mat4 cameraProjection = camera.getProjectionMatrix();

			std::cout << "Rendering gizmo of entity with id: " << m_pCurrentlySelectedEntity->getID() << "\n";

			TransformComponent& refTransformComponent = m_pCurrentlySelectedEntity->GetComponent<TransformComponent>();

			glm::mat4 modelMatrix = refTransformComponent.getTransformMatrix();

			ImGuizmo::Manipulate(
				glm::value_ptr(cameraView),
				glm::value_ptr(cameraProjection),
				operation,
				ImGuizmo::LOCAL,
				glm::value_ptr(modelMatrix)
			);

			refTransformComponent.decomposeTransformToVectors(modelMatrix);
		}
	}

	// Setting up new frame.
	void NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
		ImGuizmo::Enable(true);

		// Create the docking environment
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
			ImGuiWindowFlags_NoBackground;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
		ImGui::PopStyleVar(3);

		ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

		ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::End();
	}
};

class RealXEngine
{
	GUI* m_pGUI;			// Graphical User Interaface (GUI) will be used for creating widgets (scene, inspector, logs).
	Scene* m_pCurrentScene;	// Currently rendered scene that contains all ECS systems and entities.
	Window* m_pWindow;		// Window that contains GLFW context, that will be our canvas to put GUI and the rendered scene.

	bool defaultInitialization = false;		// Flag about if default constructor was invoken.
	bool firstRunning = true;				// Flag about if this is a first running (first frame of the engine).

public:
	
	// Default constructor.
	RealXEngine()
	{
		m_pGUI = new GUI();
		m_pWindow = new Window();
		m_pCurrentScene = new Scene();
		defaultInitialization = true;
	}

	// Initializing the engine.
	void Init()
	{
		// Initializing the window.
		m_pWindow->Init();

		// Initializing GUI.
		m_pGUI->Init(m_pWindow);

		// Initializing SCENE.
		m_pCurrentScene->Init();

		// Setting up default SCENE.
		if (defaultInitialization)
			m_pCurrentScene->SetUpExampleScene();

		// Setting up currently selected entity for GUI.
		m_pGUI->SetCurrentEntity(m_pCurrentScene->getEntities()[0]);
	}

	// Running the engine.
	void Run()
	{
		// Running till the window is open.
		while (!m_pWindow->isWindowClosed())
		{
			// 1. Clearing the previous scene (meshes, entities, etc.)
			m_pCurrentScene->ClearPreviousScene(m_pWindow);

			// 2. Updating the scene (physics, events).
			m_pCurrentScene->UpdateScene(0.0015f, m_pWindow);

			// 3. Updating gui (widgets).
			m_pGUI->Update(m_pWindow, m_pCurrentScene);

			// 4. Rendering GUI.
			m_pGUI->Render();

			// 5. Rendering the scene.
			m_pCurrentScene->RenderScene(m_pWindow);

			// Using camera.
			if (m_pWindow->isKeyPressed(GLFW_KEY_C) || !firstRunning)
			{
				Camera* camera = m_pCurrentScene->getCamera();
				firstRunning = true;
				camera->MouseHandler(m_pWindow->getDeltaX(), m_pWindow->getDeltaY(), true);
				if (m_pWindow->isKeyPressed(GLFW_KEY_ESCAPE))
					m_pWindow->Close();
				if (m_pWindow->isKeyPressed(GLFW_KEY_W))
				{
					camera->KeyBoardHandler(CameraMovement::CAMERA_FORWARD, 0.05f);
					m_pCurrentScene->getLogs().push_back("W key is pressed!");
				}
				if (m_pWindow->isKeyPressed(GLFW_KEY_A))
				{
					camera->KeyBoardHandler(CameraMovement::CAMERA_LEFT, 0.05f);
					m_pCurrentScene->getLogs().push_back("A key is pressed!");
				}
				if (m_pWindow->isKeyPressed(GLFW_KEY_S))
				{
					camera->KeyBoardHandler(CameraMovement::CAMERA_BACKWARD, 0.05f);
					m_pCurrentScene->getLogs().push_back("S key is pressed!");
				}
				if (m_pWindow->isKeyPressed(GLFW_KEY_D))
				{
					camera->KeyBoardHandler(CameraMovement::CAMERA_RIGHT, 0.05f);
					m_pCurrentScene->getLogs().push_back("D key is pressed!");
				}
			}
		}
	}
};
#endif