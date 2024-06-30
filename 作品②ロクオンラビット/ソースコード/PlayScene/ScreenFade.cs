using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using NaughtyAttributes;

public class ScreenFade : MonoBehaviour
{
    [SerializeField, Tooltip("右向きに動くパネル")]
    private RectTransform[] m_rightPanels;

    [SerializeField, Tooltip("左向きに動くパネル")]
    private RectTransform[] m_leftPanels;

    [SerializeField, Tooltip("フェードの動き用のAnimationCurve")]
    private AnimationCurve m_fadeCurve;

    [SerializeField, Tooltip("動作時間")]
    private float m_playTime;

    [ShowNonSerializedField] private bool m_isFadeOut;            //  フェードアウト動作中
    [ShowNonSerializedField] private bool m_isFadeIn;             //  フェードイン動作中

    private float m_screenWidth;         //  画面の横の大きさ
    private float m_timer;               //  動作時間計測
    private bool m_beforeOut;            //  前フレームのフェードアウト動作
    private bool m_beforeIn;             //  前フレームのフェードイン動作

    private void Start()
    {
        //  画面サイズ取得
        m_screenWidth = Screen.width;

        //  初期化
        m_timer = 0f;
        m_isFadeOut = false;
        m_isFadeIn  = false;
        m_beforeOut = false;
        m_beforeIn  = false;
    }

    private void Update()
    {
        //  前フレーム確認用のフラグを更新
        m_beforeOut = m_isFadeOut;
        m_beforeIn = m_isFadeIn;

        //  動作時間になったら動きを止める
        if (m_timer >= m_playTime)
        {
            m_isFadeOut = false;
            m_isFadeIn = false;
            return;
        }

        //  タイマーの更新
        m_timer += Time.deltaTime;

        //  経過時間の割合を計算
        float rate = m_timer / m_playTime;

        //  AnimationCurveを適用
        float curve = m_fadeCurve.Evaluate(rate);

        //  フェードアウトが動作中の場合
        if (m_isFadeOut)
        {
            //  移動先の計算
            float rightMove = Mathf.Lerp(-m_screenWidth, 0f, curve);
            float leftMove  = Mathf.Lerp(m_screenWidth, 0f, curve);

            //  移動処理
            foreach (var p in m_rightPanels)
            {
                p.localPosition = new Vector3(rightMove, p.localPosition.y, 0f);
            }

            foreach (var p in m_leftPanels)
            {
                p.localPosition = new Vector3(leftMove, p.localPosition.y, 0f);
            }
        }
        //  フェードインが動作中の場合
        else if (m_isFadeIn)
        {
            //  移動先の計算
            float rightMove = Mathf.Lerp(0f, m_screenWidth, curve);
            float leftMove = Mathf.Lerp(0f, -m_screenWidth, curve);

            //  移動処理
            foreach (var p in m_rightPanels)
            {
                p.localPosition = new Vector3(rightMove, p.localPosition.y, 0f);
            }

            foreach (var p in m_leftPanels)
            {
                p.localPosition = new Vector3(leftMove, p.localPosition.y, 0f);
            }
        }
    }

    /// <summary>
    /// フェードアウト(画面が暗くなる)の再生開始
    /// </summary>
    [Button("フェードアウトテスト")]
    public void PlayFadeOut()
    {
        //  フェードインが実行中ならフェードアウトできないようにする
        if (m_isFadeIn) return;

        //  フラグの変更
        m_isFadeOut = true;
        m_timer = 0f;

        //  初期位置へ設置
        foreach (var p in m_rightPanels)
        {
            p.localPosition = new Vector3(-m_screenWidth, p.localPosition.y, 0f);
        }

        foreach (var p in m_leftPanels)
        {
            p.localPosition = new Vector3(m_screenWidth, p.localPosition.y, 0f);
        }
    }

    /// <summary>
    /// フェードアウトの再生が終わった瞬間trueを返す
    /// </summary>
    public bool EndFadeOut()
    {
        return !m_isFadeOut && m_beforeOut;
    }

    /// <summary>
    /// フェードイン(画面を明るくする)の再生開始
    /// </summary>
    [Button("フェードインテスト")]
    public void PlayFadeIn()
    {
        //  フェードアウトが実行中ならフェードインできないようにする
        if (m_isFadeOut) return;

        //  フラグの変更
        m_isFadeIn = true;
        m_timer = 0f;

        //  初期位置へ設置
        foreach (var p in m_rightPanels)
        {
            p.localPosition = new Vector3(0f, p.localPosition.y, 0f);
        }

        foreach (var p in m_leftPanels)
        {
            p.localPosition = new Vector3(0f, p.localPosition.y, 0f);
        }
    }

    /// <summary>
    /// フェードインの再生が終わった瞬間tureを返す
    /// </summary>
    /// <returns></returns>
    public bool EndFadeIn()
    {
        return !m_isFadeIn && m_beforeIn;
    }
}
