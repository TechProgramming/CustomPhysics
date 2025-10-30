#pragma once


class World
{
protected:
	//Represents elapsed time since last fixed tick
	float AccumulatedFixedTime;

public:
	//Represents time between fixed ticks
	float TargetFixedStep;

	World();

	//For initialization
	void Init();

	//For update logic
	void Tick();

	//For physics update logic
	void TickFixed();

	//For drawing
	void Draw();

	//For cleanup and termination
	void Exit();

	//Determines whether or not the world needs to shut down
	//Returns True if shutdown needed, otherwise false
	bool ShouldClose() const;

	//Determines whether the world needs to perform a fixed tick
	//Returns True if needs TickFixed(), otherwise false
	bool ShouldTickFixed() const;

protected:
	//Runs at the end of Init()
	virtual void OnInit() {};

	//Runs at the end of Tick()
	virtual void OnTick() {};

	//Runs at the end of TickFixed()
	virtual void OnTickFixed() {};

	//Runs at the end of Draw()
	virtual void OnDraw() {};

	//Runs at the start of Exit()
	virtual void OnExit() {};
};