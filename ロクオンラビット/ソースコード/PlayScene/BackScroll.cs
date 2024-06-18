using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using NaughtyAttributes;

public class BackScroll : MonoBehaviour
{
    [SerializeField, Tooltip("動く速度")]
    private float m_moveSpeed;

    [SerializeField, Tooltip("ループするかどうか")]
    private bool m_loop;

    [SerializeField, Tooltip("プレイヤー")]
    private GameObject m_player;

    [SerializeField, ShowIf("_loop"), Tooltip("左端の位置")]
    private float m_leftEdge;
    [SerializeField, ShowIf("_loop"), Tooltip("右端の位置")]
    private float m_rightEdge;

    [SerializeField, HideIf("_loop"), Tooltip("スクロールの左端")]
    private float m_leftScrollEdge;
    [SerializeField, HideIf("_loop"), Tooltip("スクロールの右端")]
    private float m_RightScrollEdge;


    //  プレイヤーのスタート位置
    private Vector3 m_playerStartPosition;

    //  背景のスクロールのスタート位置
    private Vector3 m_startScrollPosition;

    private void Start()
    {
        //  プレイヤーのスタート位置を保持
        m_playerStartPosition = m_player.transform.position;

        //  スクロールの開始位置を保持
        m_startScrollPosition = this.transform.localPosition;
    }

    private void Update()
    {
        //  動きがループなのかどうかで動きを変える
        if (m_loop)
        {
            LoopScroll();
        }
        else
        {
            Scroll();

        }
    }

    //  スクロール
    private void Scroll()
    {
        //  プレイヤーの現在位置を取得
        Vector3 nowPlayerPosition = m_player.transform.position;

        //  プレイヤーが一定の場所より
        if (nowPlayerPosition.x < m_leftScrollEdge || nowPlayerPosition.x > m_RightScrollEdge)
        {
            return;
        }

        //  スタートの位置から横方向にどれだけ移動しているかを計算
        float deltaX = nowPlayerPosition.x - m_playerStartPosition.x;

        //  移動方向の反転（プレイヤーが右に動くと背景は左に動く）
        deltaX *= -1f;

        //  プレイヤーの場所に応じて、背景を個別の速度でスクロール
        this.transform.localPosition = new Vector3(m_startScrollPosition.x + deltaX * m_moveSpeed, 
            this.transform.localPosition.y,
            this.transform.localPosition.z);
    }

    //  ループスクロール
    private void LoopScroll()
    {
        //  一定速度で左に移動
        this.transform.localPosition += new Vector3(-m_moveSpeed, 0f, 0f);

        if (this.transform.localPosition.x < m_leftEdge)
        {
            this.transform.localPosition = new Vector3(m_rightEdge,
                this.transform.localPosition.y,
                this.transform.localPosition.z);
        }
    }
}
