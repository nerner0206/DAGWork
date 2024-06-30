using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventGimmickSE : PlayGimmickSE
{
    [SerializeField, Tooltip("�h�A�̃X�N���v�g")]
    private EventGimmick m_eventGimmick;

    public override AudioSource GetAudioSource()
    {
        return base.GetAudioSource();
    }

    public override void OnEvent()
    {
        //  �h�A���J��
        m_eventGimmick.Event();
    }
}
