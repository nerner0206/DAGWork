using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class Warp : MonoBehaviour
{
    [SerializeField, Tooltip("もう一つのワープ先")]
    private Warp m_warp;

    //  ワープしてきたか
    private bool m_warping;

    //  ワープの受け渡し
    public bool GetSetWarping
    {
        get { return m_warping; }
        set { m_warping = value; }
    }

    private void Start()
    {
        m_warping = false;
    }

    //  当たった
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  ワープしてきた又はプレイヤー以外は処理しない
        if (m_warp.GetSetWarping || !collision.gameObject.CompareTag("Player")) return;

        //  ワープに入った
        m_warping = true;
        //  移動させる
        collision.gameObject.transform.position = m_warp.transform.position;
    }
    //  外れた
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (m_warp.GetSetWarping) m_warp.GetSetWarping = false;
    }
}
