using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class EditShapeManager : MonoBehaviour
{
    //  �Q�[���p�b�h
    private Gamepad gamepad;

    //  �I�����Ă���I�u�W�F�N�g�̐ݒ�
    private GameObject selectObject;

    //  �f�b�h�]�[��
    [SerializeField] private float DEAD_ZONE = 0.1f;

    //  �ړ����x
    [SerializeField] private float MOVE_SPEED = 1.0f;
    //  ��]���x
    [SerializeField] private float ROT_SPEED = 1.0f;
    //  �g�呬�x
    [SerializeField] private float SCA_SPEED = 1.0f;

    private Vector3 objScreenPos;

    //  �f�t�H���g
    private Vector3 defPos;
    private Vector3 defRot;
    private Vector3 defSca;

    //  �}�e���A��
    [SerializeField] private Material def;
    [SerializeField] private Material line;

    //  �I�������I�u�W�F�N�g��ݒ�
    public void SetSelectObject(GameObject select)
    {
        //  �I�u�W�F�N�g��n��
        selectObject = select;
        //  �}�e���A���̕ύX
        selectObject.GetComponent<MeshRenderer>().material = line;

        defPos = selectObject.transform.position;
        defRot = selectObject.transform.eulerAngles;
        defSca = selectObject.transform.localScale;
    }
    public GameObject GetSelectObject()
    {
        return selectObject;
    }
    //  �I�������I�u�W�F�N�g���O��
    public void ResetSelectObject()
    {
        //  �}�e���A���̕ύX
        selectObject.GetComponent<MeshRenderer>().material = def;
        //  �I�u�W�F�N�g���O��
        selectObject = null;
    }
    //  ���C���΂�
    public bool FlyingRay(Vector3 iconPos, Vector3 camPos)
    {
        //  ���C���΂����������߂�(x,z���W��)
        Vector3 dec = (-2.0f * new Vector3(camPos.x, 0.0f, camPos.z)).normalized;
        //  �ŏ��̍��W
        Vector3 start = Camera.main.ScreenToWorldPoint(iconPos);

        //  �����蔻�����郌�C�𐶐�
        RaycastHit hit = new RaycastHit();
        //  ���̃��C���΂��ĐڐG���Ă��邩���肷��
        Ray ray = new Ray(start, dec);

        if (Physics.SphereCast(ray, 0.5f, out hit, 100f, LayerMask.GetMask("Target")))
        {
            //  ���������I�u�W�F�N�g��I����Ԃɂ���
            SetSelectObject(hit.transform.gameObject);
            return true;
        }

        return false;
    }

    //  �}�`�̕ҏW�X�V����
    public void EditShapeUpdate()
    {
        //  �Q�[���p�b�h�擾
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        //  �I���I�u�W�F�N�g��������Ώ������Ȃ�
        if (selectObject == null) return;

        //  �ړ�
        ShapeMove();
        //  ��]
        ShapeRot();
        //  �g��
        ShapeScale();
    }
    //  �}�`���폜
    public void DeleteShape()
    {
        //  �폜����
        Destroy(selectObject);

        selectObject = null;
    }
    public Vector3 GetObjScreenPos()
    {
        return objScreenPos;
    }

    //  �ړ�
    private void ShapeMove()
    {
        //  ���͂��󂯎��
        Vector2 input = gamepad.leftStick.ReadValue();
        //  ���͂��������ꍇ�������Ȃ�
        if (Mathf.Abs(input.x) < DEAD_ZONE && Mathf.Abs(input.y) < DEAD_ZONE) return;

        //  �I�u�W�F�N�g�̃X�N���[�����W���擾
        objScreenPos = Camera.main.WorldToScreenPoint(selectObject.transform.position);
        //  ���͂ɉ����č��W�����炷
        objScreenPos += new Vector3(input.x * Time.deltaTime * MOVE_SPEED, input.y * Time.deltaTime * MOVE_SPEED, 0.0f);

        Debug.Log(objScreenPos);

        //  �ړ��͈͂����яo������C������
        if (objScreenPos.y < 105) objScreenPos.y = 105;
        else if (objScreenPos.y > 760.0f) objScreenPos.y = 760.0f;
        if (objScreenPos.x < Screen.width / 2.0f - 576.0f) objScreenPos.x = Screen.width / 2.0f - 576.0f;
        if (objScreenPos.x > Screen.width / 2.0f + 576.0f) objScreenPos.x = Screen.width / 2.0f + 576.0f;

        //  ���W������
        selectObject.transform.position = Camera.main.ScreenToWorldPoint(objScreenPos);
    }
    //  ��]
    private void ShapeRot()
    {
        //  ���͂��󂯎��
        Vector2 input = gamepad.rightStick.ReadValue();
        //  ���͂��������ꍇ�������Ȃ�
        if (Mathf.Abs(input.x) < DEAD_ZONE && Mathf.Abs(input.y) < DEAD_ZONE) return;

    }
    //  �g��
    private void ShapeScale()
    {
        //  ���͂��󂯎��
        float input = 0.0f;

        if (gamepad.rightTrigger.ReadValue() > DEAD_ZONE && 
            selectObject.transform.localScale.x < defSca.x * 1.5f) input = gamepad.rightTrigger.ReadValue();
        else if (gamepad.leftTrigger.ReadValue() > DEAD_ZONE &&
            selectObject.transform.localScale.x > defSca.x * 0.5f) input = -gamepad.leftTrigger.ReadValue();
        else return;

        selectObject.transform.localScale += (Vector3.one * input * Time.deltaTime * SCA_SPEED * defSca.x);
    }
}
