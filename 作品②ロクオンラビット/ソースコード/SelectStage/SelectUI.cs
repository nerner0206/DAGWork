using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using NaughtyAttributes;

public class SelectUI : MonoBehaviour
{
    [SerializeField, Tooltip("星")]
    private Image[] m_starImages;
    [SerializeField, Tooltip("ステージ画像")]
    private Image[] m_stageImages;
    [SerializeField, Tooltip("ステージタイトル")]
    private Text m_titleText;
    [SerializeField, Tooltip("ステージ説明")]
    private Text m_stageText;

    [SerializeField, Header("各ステージのタイトル")]
    private string[] m_titles;
    [SerializeField, ResizableTextArea, Header("各ステージの説明文")]
    private string[] m_stageInfos;

    public void SetUI(int num)
    {
        //  星の数
        SetStar(num);
        SetStage(num);
        SetText(num);
    }

    private void SetStar(int num)
    {
        //  全非表示
        for (int i = 0; i < m_starImages.Length; i++)
        {
            m_starImages[i].enabled = false;
        }

        //  数分表示
        for (int i = 0; i < num + 1; i++)
        {
            m_starImages[i].enabled = true;
        }
    }
    private void SetStage(int num)
    {
        //  全非表示
        for (int i = 0; i < m_stageImages.Length; i++)
        {
            m_stageImages[i].enabled = false;
        }

        //  表示
        m_stageImages[num].enabled = true;
    }
    private void SetText(int num)
    {
        //  全非表示
        m_titleText.text = m_titles[num];
        m_stageText.text = m_stageInfos[num];
    }
}
