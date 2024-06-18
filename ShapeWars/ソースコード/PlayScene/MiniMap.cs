using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiniMap : MonoBehaviour
{
    //  �J�����̃I�u�W�F�N�g
    [SerializeField] private GameObject mainCam;
    //  �v���C���[�̃I�u�W�F�N�g
    [SerializeField] private GameObject player;

    //  �v���C���[�̂P�t���[���O�̈ʒu
    private Vector3 oldPlayerPos;

    //  ���C���J�����̂P�t���[���O�̊p�x
    private Vector3 oldCameraRot;

    // Start is called before the first frame update
    void Start()
    {
        //  �v���C���[�̈ʒu������
        oldPlayerPos = player.transform.position;

        //  �J�����̊p�x������
        oldCameraRot = mainCam.transform.localEulerAngles;
    }

    // Update is called once per frame
    void Update()
    {
        //  ���̈ʒu���i�[
        Vector3 nowPlayerPos = player.transform.position;
        //  �O�t���[���Ƃ̍���
        Vector3 pos = nowPlayerPos - oldPlayerPos;

        //  �J�����̈ʒu���ړ�������
        gameObject.transform.position += pos;

        //  ���̃J�����̊p�x
        Vector3 nowCameraRot = mainCam.transform.localEulerAngles;
        //  �O�t���[���Ƃ̍���
        Vector3 rot = nowCameraRot - oldCameraRot;

        //  ��]
        gameObject.transform.localEulerAngles += new Vector3(0.0f, rot.y, 0.0f);

        //  �Ō�ɑO�̈ʒu�E�p�x��ύX
        oldPlayerPos = nowPlayerPos;
        oldCameraRot = nowCameraRot;
    }
}
