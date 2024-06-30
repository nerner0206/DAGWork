using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using DG.Tweening;

public class MakeCamera : MonoBehaviour
{
    //  �萔(�ʒu)
    private static readonly Vector3[] CAM_POS = 
        {
        new Vector3(0.0f,1.0f,-8.0f),
        new Vector3(8.0f,1.0f,0.0f),
        new Vector3(0.0f,1.0f,8.0f),
        new Vector3(-8.0f,1.0f,0.0f)
        };
    //  �萔(��])
    private static readonly Vector3[] CAM_ROT =
        {
        new Vector3(0.0f,0.0f,0.0f),
        new Vector3(0.0f,-90.0f,0.0f),
        new Vector3(0.0f,-180.0f,0.0f),
        new Vector3(0.0f,-270.0f,0.0f)
        };

    //  �Q�[���p�b�h
    private Gamepad gamepad;

    //  �J�����̈ʒu�ԍ�
    private int num;
    //  �J�����̈ړ�����
    [SerializeField] private float moveTime = 0.5f;

    //  ��]�̕��@
    [SerializeField] private Ease ease;

    //  ���C�g��
    [SerializeField] private GameObject lighting;

    // Start is called before the first frame update
    void Start()
    {
        num = 0;
    }

    // Update is called once per frame
    public void CamRot()
    {
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        if(gamepad.rightShoulder.wasPressedThisFrame)
        {
            //  �l�𑝂₷
            num++;
            if (num > CAM_POS.Length - 1) num = 0;

            //  �ړ�������
            gameObject.transform.DOMove(CAM_POS[num], moveTime).SetEase(ease);
            //  ��]������
            gameObject.transform.DORotate(CAM_ROT[num], moveTime).SetEase(ease);
            //lighting.transform.DORotate(new Vector3(45.0f, CAM_ROT[num].y, 0.0f), moveTime).SetEase(ease);
        }
        else if (gamepad.leftShoulder.wasPressedThisFrame)
        {
            //  �l�𑝂₷
            num--;
            if (num < 0) num = CAM_POS.Length - 1;

            //  �ړ�������
            gameObject.transform.DOMove(CAM_POS[num], moveTime).SetEase(ease);
            //  ��]������
            gameObject.transform.DORotate(CAM_ROT[num], moveTime).SetEase(ease);
            //lighting.transform.DORotate(new Vector3(45.0f, CAM_ROT[num].y, 0.0f), moveTime).SetEase(ease);
        }
    }
}
