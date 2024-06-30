using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHaveSound : MonoBehaviour
{
    [SerializeField, Tooltip("���̍ő及����")]
    private int m_maxHaveSound = 1;

    [SerializeField, Tooltip("���ύX�@")]
    private List<PlayChanger> m_changers;

    [SerializeField, Tooltip("UI�Ǘ�")]
    private UIManager m_uI;

    [SerializeField, Tooltip("�T�E���h�̃v���n�u")]
    private GameObject m_soundPrefab;

    //  �������Ă��鉹
    private AudioClip[] m_haveAudios;
    //  ���̎��
    private SoundKind[] m_haveSounds;
    //  ���̍Đ����@�L�^
    private bool[] m_soundPlays;
    //  ���炷�p
    private AudioSource m_audioSource;      

    //  ���˕���
    private Vector2 m_dir;
    //  GUIStyle
    private GUIStyle m_style;
    //  �T�E���h
    private GameObject m_sound;

    //  �t�H���g�T�C�Y�̒萔
    const int FONT_SIZE = 50;

    //  ������
    public void Init()
    {
        //  ���������Ă�����
        if (m_sound != null)
        {
            //  �폜
            Destroy(m_sound);
            m_sound = null;
        }

        m_haveAudios = new AudioClip[m_maxHaveSound];
        m_haveSounds = new SoundKind[m_maxHaveSound];
        m_soundPlays = new bool[m_maxHaveSound];
        for (int i = 0; i < m_maxHaveSound; i++)
        {
            m_haveAudios[i] = null;
            m_haveSounds[i] = SoundKind.Over;
            m_soundPlays[i] = true;
        }

        m_audioSource = gameObject.GetComponent<AudioSource>();

        m_dir = Vector2.right;

        m_style = new GUIStyle();
        m_style.fontSize = FONT_SIZE;
        //  �t�Đ��@�������
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(true);
            }
        }
        UISet();
    }
    //  �w�肵�����̍Đ�
    public void Play()
    {
        //  �擪�̉����Ȃ�
        if (m_haveAudios[0] == null) return;

        //  ���������Ă�����
        if (m_sound != null)
        {
            //  �폜
            Destroy(m_sound);
            m_sound = null;
        }

        //  ��������
        m_sound = Instantiate(m_soundPrefab, gameObject.transform.position, Quaternion.identity);
        //  ������
        m_sound.GetComponent<SoundIcon>().Init(gameObject.transform, m_soundPlays[0],
            m_haveSounds[0], m_haveAudios[0]);

        //  UI�̕ύX
        UISet();
    }
    public void Stop()
    {
        Destroy(m_sound);

        m_sound = null;
    }
    //  �^��
    public void Recording(AudioClip audioClip, SoundKind soundKind)
    {
        //  �������܂��Ă�����
        if(m_haveSounds[m_maxHaveSound - 1] != SoundKind.Over)
        {
            //  �擪�̉����폜����
            //DeleteAudio();

            //  �擪�̉��ƌ�������
            m_haveAudios[0] = audioClip;
            m_haveSounds[0] = soundKind;
            m_soundPlays[0] = true;
            //  UI�ύX
            UISet();
            //  �����I��
            return;
        }

        //  �擪���珇�Ԃɋ󂢂Ă��邩�m�F���ċ󂢂Ă���ꏊ�Ɋi�[
        for (int i = 0; i < m_maxHaveSound; i++)
        {
            if (m_haveAudios[i] != null) continue;

            //  ���̏����擾
            m_haveAudios[i] = audioClip;
            m_haveSounds[i] = soundKind;
            m_soundPlays[i] = true;

            break;
        }


        //  �t�Đ��@�������
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(m_soundPlays[0]);
            }
        }
        UISet();
    }
    //  �폜
    public void DeleteAudio()
    {
        //  �O�ɋl�߂�
        for (int i = 1; i < m_maxHaveSound; i++)
        {
            m_haveAudios[i - 1] = m_haveAudios[i];
            m_haveSounds[i - 1] = m_haveSounds[i];
            m_soundPlays[i - 1] = m_soundPlays[i];
        }
        //  �Ō�����󂯂�
        m_haveAudios[m_maxHaveSound - 1] = null;
        m_haveSounds[m_maxHaveSound - 1] = SoundKind.Over;
        m_soundPlays[m_maxHaveSound - 1] = true;

        UISet();
    }
    //  ���̕ύX
    public void SoundChange()
    {
        int n = 0;
        //  ���������Ă���ő�̐����擾
        for(int i = 0; i < m_maxHaveSound; i++)
        {
            //  ���[�v�𔲂���
            if (m_haveSounds[i] == SoundKind.Over) break;

            n = i + 1;
        }
        //  1�ȉ��Ȃ珈�����Ȃ�
        if (n <= 1) return;

        //  �ŏ��̉����L�^
        AudioClip clip = m_haveAudios[0];
        SoundKind s = m_haveSounds[0];
        //  �Đ��󋵂��L�^
        bool play = m_soundPlays[0];

        //  ����ύX
        for(int i = 1; i < n;i++)
        {
            m_haveAudios[i - 1] = m_haveAudios[i];
            m_haveSounds[i - 1] = m_haveSounds[i];
            m_soundPlays[i - 1] = m_soundPlays[i];
        }
        m_haveAudios[n - 1] = clip;
        m_haveSounds[n - 1] = s;
        m_soundPlays[n - 1] = play;


        //  �t�Đ��@�������
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(m_soundPlays[0]);
            }
        }

        //  ui��ύX
        if (m_uI != null) m_uI.SetSoundIconUI(m_haveSounds, m_soundPlays);
    }
    public void UISet()
    {

        //  ui��ύX
        if (m_uI != null) m_uI.SetSoundIconUI(m_haveSounds, m_soundPlays);
    }
    //  �n��
    public AudioClip GetAudioClip(int num)
    {
        //  �ԍ����ő�l�𒴂��Ă����珈�����Ȃ�
        if (num > m_maxHaveSound) return null;

        return m_haveAudios[num - 1];
    }
    //  �擾
    public void SetAudioClip(AudioClip audioClip, int num)
    {
        //  �ԍ����ő�l�𒴂��Ă����珈�����Ȃ�
        if (num > m_maxHaveSound) return;

        m_haveAudios[num - 1] = audioClip;
    }
    //  �n��
    public SoundKind GetSound(int num)
    {
        //  �ԍ����ő�l�𒴂��Ă����珈�����Ȃ�
        if (num > m_maxHaveSound) return SoundKind.Over;

        return m_haveSounds[num - 1];
    }
    //  �擾
    public void SetSound(SoundKind sounds, int num)
    {
        //  �ԍ����ő�l�𒴂��Ă����珈�����Ȃ�
        if (num > m_maxHaveSound) return;

        m_haveSounds[num - 1] = sounds;
    }

    //  �n��
    public int GetMaxHaveSound()
    {
        return m_maxHaveSound;
    }

    public void PlayBack()
    {
        //  �����Ȃ���Ώ������Ȃ�
        if (m_haveSounds[0] == SoundKind.Over) return;

        //  �Đ������𔽓]������
        m_soundPlays[0] = !m_soundPlays[0];


        //  �t�Đ��@�������
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(m_soundPlays[0]);
            }
        }
        //  UI�̕ύX
        m_uI.SetSoundIconUI(m_haveSounds, m_soundPlays);
    }
}
