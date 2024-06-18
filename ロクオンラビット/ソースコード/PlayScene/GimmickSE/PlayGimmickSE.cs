using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CircleCollider2D))]
public class PlayGimmickSE : GimmickSE
{
    //  ‰~‚Ì“–‚½‚è”»’è
    private CircleCollider2D m_co2D = null;

    public void Init()
    {
        //  ‰¹‚Ìí—Ş‚ğÁ‚·
        m_soundKind = SoundKind.Over;
        //  ‰~‚Ì“–‚½‚è”»’è
        m_co2D = gameObject.GetComponent<CircleCollider2D>();
        //  “–‚½‚è”»’èÁ‚·
        m_co2D.enabled = false;
    }
    public void OnGimmickSE(SoundKind kind)
    {
        //  ‰¹‚Ìí—Ş
        m_soundKind = kind;

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
}
