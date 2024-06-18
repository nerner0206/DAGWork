using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    //  プレイヤーの情報
    private Transform m_player;

    //  ギミック音
    private GimmickSE[] m_gimmickSEs;
    //  プレイ音
    private GameObject[] m_playGimmicks;
    //  AudioSources
    private AudioSource[] m_audioSources;

    //  初期化
    public void SoundManagerInit(Transform pPos)
    {
        //  存在しているGimmickSEを全て取得
        m_gimmickSEs = GameObject.FindObjectsOfType<GimmickSE>();

        m_audioSources = new AudioSource[m_gimmickSEs.Length];

        for (int i = 0; i < m_gimmickSEs.Length; i++)
        {
            m_audioSources[i]= m_gimmickSEs[i].GetAudioSource();
        }

        //  プレイヤーの位置を取得
        m_player = pPos;
    }

    //  更新
    public void SoundManagerUpdate()
    {
        //  音が無ければ処理しない
        if (m_gimmickSEs.Length < 0) return;
        //  繰り返す
        for (int i = 0; i < m_gimmickSEs.Length; i++)
        {
            if (m_gimmickSEs[i] == null) continue;
            
            //  ギミック音とプレイヤーの距離を測る
            float distance = Vector3.Distance(m_player.position, m_gimmickSEs[i].gameObject.transform.position);
            //  最大距離との割合
            float vol = m_gimmickSEs[i].GetMaxSound() - (distance / m_gimmickSEs[i].GetListenSoundRange());
            //  音量がマイナスになったら０に戻す
            if (vol < 0) vol = 0f;
            //  音量を設定
            m_audioSources[i].volume = vol;
        }
    }
}
