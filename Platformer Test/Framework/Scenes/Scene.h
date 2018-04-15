#ifndef SCENE_BASE_H
#define SCENE_BASE_H

class SceneManager;

class Scene
{
public:

	Scene();
	~Scene();

	void SetRunning(bool b);
	bool IsRunning();

	Scene* GetParent();
	Scene* GetChild();
	void SetParent(Scene* sc);
	void SetChild(Scene* sc);

	SceneManager* GetManager();
	void SetManager(SceneManager* sm);

	//	Begin & End, Pause & Resume, Update & DrawScreen
	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update(float dt) = 0;
	virtual void DrawScreen() = 0;

private:

	SceneManager* _ManagerPntr;
	Scene* _ParentPntr;
	Scene* _ChildPntr;
	bool _Running;
};

class SceneTransition
{
public:

	virtual void Update(float dt) = 0;
	virtual void DrawScreen() = 0;

	Scene* _Scene1 = 0;
	Scene* _Scene2 = 0;
	SceneManager* _ManagerPntr = 0;
};

class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	void PushScene(Scene* new_scene, SceneTransition* scene_transition = 0);

	void CullScenes();

	void Quit(int i = -1);

	Scene* GetActiveScenePntr();

	Scene* GetRootScenePntr();

	SceneTransition* GetTransitionPntr();
	void CompleteTransition();

private:

	Scene* _RootScenePntr;
	SceneTransition* _TransitionPntr;
};

#endif