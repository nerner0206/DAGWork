using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class UIManager : MonoBehaviour
{
    [SerializeField, Tooltip("UIの親")]
    private GameObject m_parent;

    [SerializeField, Header("音のアイコン")]
    private List<GameObject> m_soundIconsPrefab;
    [SerializeField, Header("音のアイコンフレーム")]
    private GameObject[] m_soundFrames;

    [SerializeField, Tooltip("収集要素の設定")]
    private GameObject[] m_collectItems;
    [SerializeField, Tooltip("再生状況のアイコン")]
    private GameObject[] m_playIcons = new GameObject[2];

    //  持てる最大の数
    private int m_maxNum;

    //  クリアCanvas
    [SerializeField] private ClearUIManager m_clear;

    //  コントローラー
    private PlayerControll m_controll;

    //  リスタートObj
    [SerializeField] private GameObject m_reStartObj;
    //  ゲージ
    [SerializeField] private Image m_reStartGage;
    //  リスタート時間
    [SerializeField] private float m_reStartTime;
    //  リスタートタイマー
    private float m_reStartTimer;

    [SerializeField, Tooltip("簡易フェイドインアウト用")]
    private ScreenFade m_fade;

    //  UIの非表示
    public void Non()
    {
        m_parent.SetActive(false);
    }
    //  UIの表示
    public void On()
    {
        m_parent.SetActive(true);
    }

    //  初期化
    public void UIManagerInit(PlayerHaveSound p, PlayerControll inputActions)
    {
        //  コントローラー
        m_controll = inputActions;

        //  音を持てる最大の数を取得
        m_maxNum = p.GetMaxHaveSound();

        //  持てる数までUIを減らす
        for (int i = m_maxNum; i < m_soundFrames.Length; i++)
        {
            m_soundFrames[i].SetActive(false);
        }
        //  初期化
        for (int i = 0; i < m_collectItems.Length; i++)
        {
            m_collectItems[i].SetActive(false);
        }

        //  リスタートゲージ
        m_reStartTimer = 0f;
    }
    //  UIの更新
    public bool UIUpdate()
    {
        //  押したら
        if(m_controll.PlaySceneUI.ReStart.WasPressedThisFrame())
        {
            //  RestartUI表示
            m_reStartObj.SetActive(true);
            //  タイマーの初期化
            m_reStartTimer = 0f;
        }

        //  離したら
        if(m_controll.PlaySceneUI.ReStart.WasReleasedThisFrame())
        {
            //  RestartUI非表示
            m_reStartObj.SetActive(false);
        }
        //  長押し中
        else if(m_controll.PlaySceneUI.ReStart.ReadValue<float>() > 0.5f)
        {
            //  時間を増やす
            m_reStartTimer += Time.deltaTime;

            m_reStartGage.fillAmount = m_reStartTimer / m_reStartTime;

            if (m_reStartTimer >= m_reStartTime)
            {
                //  UIの非表示
                m_reStartObj.SetActive(false);
                return true;
            }
        }

        return false;
    }

    //  クリア更新の真偽値の取得
    public bool ClearUIUpdate()
    {
        return m_clear.ClearUIUpdate();
    }
    //  選択番号の取得
    public int ClearUISelectNumber()
    {
        return m_clear.ClearSelectNum();
    }

    //  取得した音のアイコンの設定
    public void SetSoundIconUI(SoundKind[] soundKinds, bool[] playbacks)
    {
        for (int i = 0; i < soundKinds.Length; i++)
        {
            int n = m_soundFrames[i].transform.childCount;

            //  音のアイコンを削除する
            for (int j = 0; j < n; j++)
            {
                Destroy(m_soundFrames[i].transform.GetChild(j).gameObject);
            }

            //  音が無ければ処理しない
            if (soundKinds[i] == SoundKind.Over) continue;

            int num = (int)soundKinds[i];
            if (num > (int)SoundKind.Over) num = (int)SoundKind.Over;

            //  音に合ったオブジェクトを生成する
            GameObject icon = Instantiate(m_soundIconsPrefab[num], m_soundFrames[i].transform);
            icon.transform.localPosition = Vector3.zero;

            //  再生アイコン
            GameObject playIcon = null;
            //  普通再生
            if (playbacks[i]) playIcon = Instantiate(m_playIcons[0], icon.transform);
            //  逆再生
            else playIcon = Instantiate(m_playIcons[1], icon.transform);

            RectTransform rect = playIcon.GetComponent<RectTransform>();
            //  大きさの変更
            if (i != 0)
            {
                icon.GetComponent<RectTransform>().sizeDelta = new Vector2(90, 90);
                rect.localPosition = new Vector3(20, -20, 0);
                rect.sizeDelta = new Vector2(66, 66);
            }
            else
            {
                icon.GetComponent<RectTransform>().sizeDelta = new Vector2(140, 140);
                rect.localPosition = new Vector3(30, -30, 0);
            }
            
        }
    }

    //  収集要素の設定
    public void SetTapeUI(bool[] flags)
    {
        for (int i = 0; i < flags.Length; i++)
        {
            if (flags[i]) m_collectItems[i].SetActive(true);
        }
    }

    //  クリア画面の表示
    public void Clear(float time, int tapeNum)
    {
        //  クリアUIの表示
        m_clear.gameObject.SetActive(true);
        //  表示
        m_clear.ClearDisplay(time, m_controll, tapeNum);
    }

    //  クリアが目の非表示
    public void ClearReset()
    {
        m_clear.gameObject.SetActive(false);
    }

    //  フェイドイン開始
    public void FadeInStart()
    {
        m_fade.PlayFadeIn();
    }
    //  フェイドアウト開始
    public void FadeOutStart()
    {
        m_fade.PlayFadeOut();
    }

    //  リスタート
    public bool ReStart()
    {
        return m_fade.EndFadeOut();
    }
}
