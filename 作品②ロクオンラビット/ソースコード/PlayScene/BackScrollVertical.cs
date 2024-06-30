using NaughtyAttributes;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackScrollVertical : MonoBehaviour
{
    [SerializeField, Tooltip("プレイヤー")]
    private GameObject m_player;

    [SerializeField, Tooltip("スクロールの上端")]
    private float m_upScrollEdge;
    [SerializeField, Tooltip("スクロールの下端")]
    private float m_downScrollEdge;
    [SerializeField, Tooltip("総移動量")]
    private float m_totalTravel;


    //  プレイヤーのスタート位置
    private Vector3 m_playerStartPosition;

    //  背景のスクロールのスタート位置
    private Vector3 m_startScrollPosition;

    //  プレイヤーの移動可能範囲
    private float m_movableRange;

    private void Start()
    {
        //  プレイヤーのスタート位置を保持
        m_playerStartPosition = m_player.transform.position;

        //  スクロールの開始位置を保持
        m_startScrollPosition = this.transform.localPosition;

        //  プレイヤーが進んだ割合計算用に移動範囲を出しておく
        m_movableRange = m_upScrollEdge - m_downScrollEdge;
    }

    //  更新
    private void Update()
    {
        //  スクロール
        Scroll();
    }

    //  スクロール
    private void Scroll()
    {
        //  プレイヤーの現在位置を取得
        Vector3 nowPlayerPosition = m_player.transform.position;

        //  プレイヤーが範囲内にいるかチェック
        if (nowPlayerPosition.y < m_downScrollEdge || nowPlayerPosition.y > m_upScrollEdge)
        {
            return;
        }

        //  スタートの位置からどれくらい縦に動いたのかの割合を計算
        float deltaY = nowPlayerPosition.y / m_movableRange;

        //  プレイヤーの場所に応じて、背景をスクロール
        float moveY = Mathf.Lerp(m_startScrollPosition.y, m_startScrollPosition.y + m_totalTravel, deltaY);
        this.transform.localPosition = new Vector3(
            this.transform.localPosition.x,
            moveY,
            this.transform.localPosition.z);
    }
}
