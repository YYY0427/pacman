#pragma once
#include <unordered_map>
#include <string>

/// <summary>
/// SE�̊Ǘ����s���V���O���g���N���X
/// </summary>
class SoundManager
{
private:
	std::unordered_map<std::string, int> nameAndHandleTable_;
	int LoadSoundFile(const char* fileName);
	SoundManager();
	~SoundManager();

	// �R�s�[��������֎~����
	SoundManager(const SoundManager&) = delete;
	void operator = (const SoundManager&) = delete;
public:
	/// <summary>
	/// SoundManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance()
	{
		// �B��̎���
		static SoundManager instance;

		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

	/// <summary>
	/// �w��̃T�E���h��炷
	/// </summary>
	/// <param name="name">�T�E���h��</param>
	void Play(const char* name);
};