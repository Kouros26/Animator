#include "Animator/animation.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"

Animation::Animation(const std::string& pPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(PROJECT_PATH + pPath, 0);

	const auto animation = scene->mAnimations[0];
	const auto meshAnim = animation->mMorphMeshChannels[0];

	for (int i = 0; i < meshAnim->mNumKeys; i++)
	{
		Key key;
		key.time = meshAnim->mKeys[i].mTime;

		for (int j = 0; j < meshAnim->mKeys[i].mNumValuesAndWeights; j++)
		{
			
		}
	}
}
