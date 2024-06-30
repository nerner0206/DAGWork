using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class MomentGimmickSE : GimmickSE
{
    [SerializeField, Tooltip("‰~‚Ì“–‚½‚è”»’è")]
    private CircleCollider2D m_co2D;
    //  ŠÔ
    private float m_timer;

    public void Init()
    {
        //  ‰¹‚Ìí—Ş‚ğÁ‚·
        m_soundKind = SoundKind.Over;
        //  “–‚½‚è”»’èÁ‚·
        m_co2D.enabled = false;

        //  ŠÔ‚ğ0‚Ö
        m_timer = 0.0f;
    }
    public void OnGimmickSE(SoundKind kind, float time)
    {
        //  ‰¹‚Ìí—Ş
        m_soundKind = kind;
        //  ‰¹æ“¾‰Â”\ŠÔ
        m_timer = time;

        //  “–‚½‚è”»’è‚ğ‚Â‚¯‚é
        m_co2D.enabled = true;
    }
    public void OffGimmickSE()
    {
        //  ‰¹‚Ìí—Ş
        m_soundKind = SoundKind.Over;

        //  “–‚½‚è”»’è‚ğ‚Â‚¯‚é
        m_co2D.enabled = false;
    }

    private void Update()
    {
        //  ‰¹‚ª–³‚¯‚ê‚Îˆ—‚µ‚È‚¢
        if (m_soundKind == SoundKind.Over) return;

        if (m_timer > 0.0f)
        {
            //  ŠÔ‚ğŒ¸‚ç‚·
            m_timer -= Time.deltaTime;
            //  •Ô‚·
            return;
        }

        //  “–‚½‚è”»’è‚ğíœ
        OffGimmickSE();
    }
}
