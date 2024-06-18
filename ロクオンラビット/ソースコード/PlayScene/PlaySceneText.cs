using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class PlaySceneText : MonoBehaviour
{
    [SerializeField, Tooltip("テキストオブジェクト")]
    private Text m_text;

    //  遅延時間の定数
    const int DELAY_TIME = 5;

    //  テキストの表示開始
    public void TextStart(string message)
    {
        //  アニメーションの実行中なら中断して次の文字を表示する
        if (DOTween.IsTweening(m_text))
        {
            m_text.DOKill();
        }

        //  テキスト初期化
        m_text.text = "";

        //  表示アニメーション
        m_text.DOText(message, 1).SetEase(Ease.Linear);

        //  文字数取得
        string space = "";
        for (int i = 0; i < message.Length; i++)
        {
            space += " ";
        }

        //  消去アニメーション
        m_text.DOText(space, 1).SetEase(Ease.Linear).SetDelay(DELAY_TIME);
    }

}
