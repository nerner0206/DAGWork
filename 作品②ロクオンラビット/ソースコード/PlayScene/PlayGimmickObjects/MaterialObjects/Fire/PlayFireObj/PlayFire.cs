using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayFire : PlayFireObj
{
    //  �X�V����
    private void Update()
    {
        //  ���̉����G��Ă��Ȃ�
        if (m_hitSoundKind == SoundKind.Over) return;

        //  �����q�b�g�����Ƃ��̏���
        switch(m_hitSoundKind)
        {
            case SoundKind.Water:
                HitWater();
                break;
            default:
                break;
        }
    }
    //  �����ڐG
    public override void HitWater()
    {
        base.HitWater();
    }
}
