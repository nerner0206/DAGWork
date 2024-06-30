//--------------------------------------------------------------------------------------
// File: AudioResources.h
//
// 音リソースクラスのヘッダーファイル（シングルトン化）
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef AUDIO_RESOURCES_DEFINED
#define AUDIO_RESOURCES_DEFINED

#include <Audio.h>

/// <summary>
/// 音リソースクラス
/// </summary>
class AudioResources
{
public:
	//	音量の最大値
	static const float MAX_VOLUME;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	AudioResources();
	/// <summary>
	///	デストラクタ
	/// </summary>
	~AudioResources();

	/// <summary>
	/// 音リソースクラスのインスタンスの取得
	/// </summary>
	/// <returns>音リソースクラスのポインタ</returns>
	static AudioResources* GetInstance()
	{
		//	ポインタが作られていない場合、新しくポインタを作成する
		if (s_audioResources.get() == nullptr) 
			s_audioResources.reset(new AudioResources());

		return s_audioResources.get();
	}

	/// <summary>
	/// BGM1の再生
	/// </summary>
	void PlayBGM1() { m_bgmInstance->Play(true); }
	/// <summary>
	/// BGM1の停止
	/// </summary>
	void StopBGM1() { m_bgmInstance->Stop(); }

	/// <summary>
	/// BGM2の再生
	/// </summary>
	void PlayBGM2() { m_playBgmInstance->Play(true); }
	/// <summary>
	/// BGM2の停止
	/// </summary>
	void StopBGM2() { m_playBgmInstance->Stop(); }

	/// <summary>
	/// 決定SEの再生
	/// </summary>
	void PlayDecideSE() { m_decideSE->Play(); }
	/// <summary>
	/// 選択SEの再生
	/// </summary>
	void PlaySelectSE() { m_selectSE->Play(); }
	/// <summary>
	/// 設定SEの再生
	/// </summary>
	void PlaySystemSE() { m_systemSE->Play(); }

	/// <summary>
	/// ばねSEの再生
	/// </summary>
	void PlaySpringSE() { m_springSE->Play(); }
	/// <summary>
	/// ジャンプSEの再生
	/// </summary>
	void PlayJumpSE() { m_jumpSE->Play(); }
	/// <summary>
	/// 爆発SEの再生
	/// </summary>
	void PlayExplosionSE() { m_explosionSE->Play(); }
	/// <summary>
	/// 破裂SEの再生
	/// </summary>
	void PlayBalloonSE() { m_balloonSE->Play(); }
	/// <summary>
	/// 風SEの再生
	/// </summary>
	void PlayWindSE() { m_windSE->Play(); }

	/// <summary>
	/// クラッカー①SEの再生
	/// </summary>
	void PlayCracker01SE() { m_cracker01SE->Play(); }
	/// <summary>
	/// クラッカー②SEの再生
	/// </summary>
	void PlayCracker02SE() { m_cracker02SE->Play(); }

	/// <summary>
	/// クリアSEの再生
	/// </summary>
	void PlayClearSE() { m_clearSE->Play(); }
	/// <summary>
	/// 死亡SEの再生
	/// </summary>
	void PlayDeadSE() { m_deadSE->Play(); }

private:
	//	音リソースクラスのポインタ
	static std::unique_ptr<AudioResources> s_audioResources;

	//	BGM1のユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_bgm;
	//	BGM1インスタンスのユニークポインタ
	std::unique_ptr<DirectX::SoundEffectInstance> m_bgmInstance;

	//	BGM2のユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_playBgm;
	//	BGM2インスタンスのユニークポインタ
	std::unique_ptr<DirectX::SoundEffectInstance> m_playBgmInstance;

	//	決定SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_decideSE;
	//	矢印SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_selectSE;
	//	設定SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_systemSE;

	//	ばねSEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_springSE;
	//	ジャンプSEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_jumpSE;
	//	爆発SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_explosionSE;
	//	破裂SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_balloonSE;
	//	風SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_windSE;

	//	クラッカー①SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_cracker01SE;
	//	クラッカー②SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_cracker02SE;

	//	クリアSEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_clearSE;
	//	死亡SEのユニークポインタ
	std::unique_ptr<DirectX::SoundEffect> m_deadSE;
};
#endif // !AUDIO_RESOURCES_DEFINED