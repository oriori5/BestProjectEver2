

#ifndef ACTIONRESULT_H_
#define ACTIONRESULT_H_

class ActionResult {
protected:
	float _monment;
	float _yawResult;
public:
	ActionResult();
	ActionResult(float monment, float yaw);
	float GetMovment();
	float GetYaw();
	virtual ~ActionResult();
};

#endif /* ACTIONRESULT_H_ */
