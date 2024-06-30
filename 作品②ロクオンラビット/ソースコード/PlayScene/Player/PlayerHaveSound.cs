using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHaveSound : MonoBehaviour
{
    [SerializeField, Tooltip("音の最大所持数")]
    private int m_maxHaveSound = 1;

    [SerializeField, Tooltip("音変更機")]
    private List<PlayChanger> m_changers;

    [SerializeField, Tooltip("UI管理")]
    private UIManager m_uI;

    [SerializeField, Tooltip("サウンドのプレハブ")]
    private GameObject m_soundPrefab;

    //  所持している音
    private AudioClip[] m_haveAudios;
    //  音の種類
    private SoundKind[] m_haveSounds;
    //  音の再生方法記録
    private bool[] m_soundPlays;
    //  音鳴らす用
    private AudioSource m_audioSource;      

    //  発射方向
    private Vector2 m_dir;
    //  GUIStyle
    private GUIStyle m_style;
    //  サウンド
    private GameObject m_sound;

    //  フォントサイズの定数
    const int FONT_SIZE = 50;

    //  初期化
    public void Init()
    {
        //  音が入っていたら
        if (m_sound != null)
        {
            //  削除
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
        //  逆再生機があれば
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(true);
            }
        }
        UISet();
    }
    //  指定した音の再生
    public void Play()
    {
        //  先頭の音がない
        if (m_haveAudios[0] == null) return;

        //  音が入っていたら
        if (m_sound != null)
        {
            //  削除
            Destroy(m_sound);
            m_sound = null;
        }

        //  生成する
        m_sound = Instantiate(m_soundPrefab, gameObject.transform.position, Quaternion.identity);
        //  初期化
        m_sound.GetComponent<SoundIcon>().Init(gameObject.transform, m_soundPlays[0],
            m_haveSounds[0], m_haveAudios[0]);

        //  UIの変更
        UISet();
    }
    public void Stop()
    {
        Destroy(m_sound);

        m_sound = null;
    }
    //  録音
    public void Recording(AudioClip audioClip, SoundKind soundKind)
    {
        //  音が埋まっていたら
        if(m_haveSounds[m_maxHaveSound - 1] != SoundKind.Over)
        {
            //  先頭の音を削除する
            //DeleteAudio();

            //  先頭の音と交換する
            m_haveAudios[0] = audioClip;
            m_haveSounds[0] = soundKind;
            m_soundPlays[0] = true;
            //  UI変更
            UISet();
            //  処理終了
            return;
        }

        //  先頭から順番に空いているか確認して空いている場所に格納
        for (int i = 0; i < m_maxHaveSound; i++)
        {
            if (m_haveAudios[i] != null) continue;

            //  音の情報を取得
            m_haveAudios[i] = audioClip;
            m_haveSounds[i] = soundKind;
            m_soundPlays[i] = true;

            break;
        }


        //  逆再生機があれば
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(m_soundPlays[0]);
            }
        }
        UISet();
    }
    //  削除
    public void DeleteAudio()
    {
        //  前に詰める
        for (int i = 1; i < m_maxHaveSound; i++)
        {
            m_haveAudios[i - 1] = m_haveAudios[i];
            m_haveSounds[i - 1] = m_haveSounds[i];
            m_soundPlays[i - 1] = m_soundPlays[i];
        }
        //  最後尾を空ける
        m_haveAudios[m_maxHaveSound - 1] = null;
        m_haveSounds[m_maxHaveSound - 1] = SoundKind.Over;
        m_soundPlays[m_maxHaveSound - 1] = true;

        UISet();
    }
    //  音の変更
    public void SoundChange()
    {
        int n = 0;
        //  音が入っている最大の数を取得
        for(int i = 0; i < m_maxHaveSound; i++)
        {
            //  ループを抜ける
            if (m_haveSounds[i] == SoundKind.Over) break;

            n = i + 1;
        }
        //  1以下なら処理しない
        if (n <= 1) return;

        //  最初の音を記録
        AudioClip clip = m_haveAudios[0];
        SoundKind s = m_haveSounds[0];
        //  再生状況を記録
        bool play = m_soundPlays[0];

        //  音を変更
        for(int i = 1; i < n;i++)
        {
            m_haveAudios[i - 1] = m_haveAudios[i];
            m_haveSounds[i - 1] = m_haveSounds[i];
            m_soundPlays[i - 1] = m_soundPlays[i];
        }
        m_haveAudios[n - 1] = clip;
        m_haveSounds[n - 1] = s;
        m_soundPlays[n - 1] = play;


        //  逆再生機があれば
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(m_soundPlays[0]);
            }
        }

        //  uiを変更
        if (m_uI != null) m_uI.SetSoundIconUI(m_haveSounds, m_soundPlays);
    }
    public void UISet()
    {

        //  uiを変更
        if (m_uI != null) m_uI.SetSoundIconUI(m_haveSounds, m_soundPlays);
    }
    //  渡す
    public AudioClip GetAudioClip(int num)
    {
        //  番号が最大値を超えていたら処理しない
        if (num > m_maxHaveSound) return null;

        return m_haveAudios[num - 1];
    }
    //  取得
    public void SetAudioClip(AudioClip audioClip, int num)
    {
        //  番号が最大値を超えていたら処理しない
        if (num > m_maxHaveSound) return;

        m_haveAudios[num - 1] = audioClip;
    }
    //  渡す
    public SoundKind GetSound(int num)
    {
        //  番号が最大値を超えていたら処理しない
        if (num > m_maxHaveSound) return SoundKind.Over;

        return m_haveSounds[num - 1];
    }
    //  取得
    public void SetSound(SoundKind sounds, int num)
    {
        //  番号が最大値を超えていたら処理しない
        if (num > m_maxHaveSound) return;

        m_haveSounds[num - 1] = sounds;
    }

    //  渡す
    public int GetMaxHaveSound()
    {
        return m_maxHaveSound;
    }

    public void PlayBack()
    {
        //  音がなければ処理しない
        if (m_haveSounds[0] == SoundKind.Over) return;

        //  再生方向を反転させる
        m_soundPlays[0] = !m_soundPlays[0];


        //  逆再生機があれば
        if (m_changers != null)
        {
            foreach (var changer in m_changers)
            {
                changer.Change(m_soundPlays[0]);
            }
        }
        //  UIの変更
        m_uI.SetSoundIconUI(m_haveSounds, m_soundPlays);
    }
}
