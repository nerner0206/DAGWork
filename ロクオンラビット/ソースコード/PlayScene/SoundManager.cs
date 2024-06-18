using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    //  �v���C���[�̏��
    private Transform m_player;

    //  �M�~�b�N��
    private GimmickSE[] m_gimmickSEs;
    //  �v���C��
    private GameObject[] m_playGimmicks;
    //  AudioSources
    private AudioSource[] m_audioSources;

    //  ������
    public void SoundManagerInit(Transform pPos)
    {
        //  ���݂��Ă���GimmickSE��S�Ď擾
        m_gimmickSEs = GameObject.FindObjectsOfType<GimmickSE>();

        m_audioSources = new AudioSource[m_gimmickSEs.Length];

        for (int i = 0; i < m_gimmickSEs.Length; i++)
        {
            m_audioSources[i]= m_gimmickSEs[i].GetAudioSource();
        }

        //  �v���C���[�̈ʒu���擾
        m_player = pPos;
    }

    //  �X�V
    public void SoundManagerUpdate()
    {
        //  ����������Ώ������Ȃ�
        if (m_gimmickSEs.Length < 0) return;
        //  �J��Ԃ�
        for (int i = 0; i < m_gimmickSEs.Length; i++)
        {
            if (m_gimmickSEs[i] == null) continue;
            
            //  �M�~�b�N���ƃv���C���[�̋����𑪂�
            float distance = Vector3.Distance(m_player.position, m_gimmickSEs[i].gameObject.transform.position);
            //  �ő勗���Ƃ̊���
            float vol = m_gimmickSEs[i].GetMaxSound() - (distance / m_gimmickSEs[i].GetListenSoundRange());
            //  ���ʂ��}�C�i�X�ɂȂ�����O�ɖ߂�
            if (vol < 0) vol = 0f;
            //  ���ʂ�ݒ�
            m_audioSources[i].volume = vol;
        }
    }
}
