using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnim : MonoBehaviour
{
    //  スタート合図の取得・設定
    public bool GetSetIsStart
    {
        get { return m_isStart; }
        set { m_isStart = value; }
    }

    //  ゲームオーバー判定の取得・設定
    public bool GetSetIsGameOver
    {
        get { return m_isGameOver; }
        set { m_isGameOver = value; }
    }

    //  攻撃の取得・設定
    public bool GetSetAttack
    {
        get { return m_attack; }
        set { m_attack = value; }
    }

    //  スタート合図
    private bool m_isStart = false;
    //  ゲームオーバー判定
    private bool m_isGameOver = false;
    //  攻撃
    private bool m_attack = false;

    //  死亡アニメーション終了
    void FinishDeadAnimation()
    {
        //  ゲームオーバー
        m_isGameOver = true;
    }
    //  開始アニメーション終了
    void FinishStartAnimation()
    {
        //  動ける
        m_isStart = true;
    }
    //  攻撃アニメーションのタイミング
    void Attack()
    {
        m_attack = true;
    }
}
