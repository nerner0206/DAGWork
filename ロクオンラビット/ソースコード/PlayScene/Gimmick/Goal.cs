using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Goal : MonoBehaviour
{
    //  ゴール判定
    private bool m_isGoal = false;

    //  取得・渡す
    public bool GetSetIsGoal
    {
        get { return m_isGoal; }
        set { m_isGoal = value; }
    }

    //  当たり判定
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  プレイヤー以外なら処理しない
        if (!collision.gameObject.CompareTag("Player")) return;

        //  ゴール
        m_isGoal = true;
    }
}
