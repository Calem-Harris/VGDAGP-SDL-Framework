#include "GameEntity.h"

namespace SDLFramework {
	GameEntity::GameEntity(float x, float y) : mPostion(x, y), mRotation(0.0f), 
												mScale(Vec2_One), mActive(true), mParent(nullptr) {

	}

	GameEntity::~GameEntity() {
		mParent = nullptr;
	}

	void GameEntity::Position(float x, float y) {
		mPostion = Vector2(x, y);
	}

	void GameEntity::Position(const Vector2& pos) {
		mPostion = pos;
	}

	Vector2 GameEntity::Position(Space space) {
		if (space == Local || mParent == nullptr) {
			return mPostion;
		}

		Vector2 parentScale = mParent->Scale(World);
		Vector2 rotPosition = RotateVector(mPostion, mParent->Rotation(Local));

		return mParent->Position(World) + Vector2(rotPosition.x * parentScale.x, rotPosition.y * parentScale.y);
	}

	void GameEntity::Rotation(float rot) {
		mRotation = rot;

		while (mRotation > 360.0f) {
			mRotation -= 360.0f;
		}

		while (mRotation < 0.0f) {
			mRotation += 360.0f;
		}
	}

	float GameEntity::Rotation(Space space) {
		if (space == Local || mParent == nullptr) {
			return mRotation;
		}

		return mParent->Rotation(World) + mRotation;
	}

	void GameEntity::Scale(Vector2 scale) {
		mScale = scale;
	}

	Vector2 GameEntity::Scale(Space space) {
		if (space == Local || mParent == nullptr) {
			return mScale;
		}

		Vector2 scale = mParent->Scale(World);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return scale;
	}

	void GameEntity::Active(bool active) {
		mActive = active;
	}

	bool GameEntity::Active() const {
		return mActive;
	}

	void GameEntity::Parent(GameEntity* parent) {
		//This is how we remove any parent object
		if (parent == nullptr) {
			mPostion = Position(World);
			mRotation = Rotation(World);
			mScale = Scale(World);
		}
		else {
			if (mParent != nullptr) {
				//We are already a child of something
				Parent(nullptr);
			}

			//At this point, we have an object we want to attach to AND
			//We have unattached from our previous object

			Vector2 parentScale = parent->Scale(World);

			mPostion = RotateVector(Position(World) - parent->Position(World), -parent->Rotation(World));
			mPostion.x /= parentScale.x;
			mPostion.y /= parentScale.y;

			mRotation -= parent->Rotation(World);
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
		}

		mParent = parent;
	}

	GameEntity* GameEntity::Parent() {
		return mParent;
	}
}