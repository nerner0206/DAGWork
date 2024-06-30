using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class MoveIcon : MonoBehaviour
{
    //  �Q�[���p�b�h
    private Gamepad gamepad;

    //  �ԍ�
    private int selectShapeNum;

    //  �f�b�h�]�[��
    [SerializeField] private float DEAD_ZONE = 0.1f;
    [SerializeField] private float DEAD_ZONE_ADD = 0.5f;
    //  �ړ����x
    [SerializeField] private float MOVE_SPEED = 5.0f;

    //  �}�`��ǉ�����UI�̈ʒu
    [SerializeField] private List<GameObject> addShapeUIs;

    private float coolTime;
    private float coolTimer;

    // Start is called before the first frame update
    private void Start()
    {
        //  �Q�[���p�b�h���擾����
        gamepad = Gamepad.current;
        //  �ŏ���0
        selectShapeNum = 0;

        coolTime = 0.2f;
    }
    private void Update()
    {
        gameObject.transform.Rotate(new Vector3(0.0f, 0.0f, 0.1f));
    }

    //  ���R�s��
    public void FreeMove()
    {
        //  ���͂��󂯎��
        Vector2 input = InputController();

        //  ��ʊO�Ɉړ������Ƃ��͖߂�
        Vector3 icon_pos = gameObject.transform.localPosition;

        //  ���͂̑傫���ɂ���Ĉړ��ʂ�ύX����
        icon_pos.x += input.x * Time.deltaTime * MOVE_SPEED;
        icon_pos.y += input.y * Time.deltaTime * MOVE_SPEED;
        
        //  �摜�̃T�C�Y���擾
        Vector2 icon_size = gameObject.GetComponent<RectTransform>().sizeDelta / 2.0f;

        //  ��ʂ̔������擾
        float width = (float)Screen.width / 2.0f;
        float height = (float)Screen.height / 2.0f;

        //  ���E
        if (icon_pos.x + icon_size.x > width) icon_pos.x = width - icon_size.x;
        else if (icon_pos.x - icon_size.x < -width) icon_pos.x = -width + icon_size.x;

        //  �㉺
        if (icon_pos.y + icon_size.y > height) icon_pos.y = height - icon_size.y;
        else if (icon_pos.y - icon_size.y < -height) icon_pos.y = -height + icon_size.y;

        gameObject.transform.localPosition = icon_pos;
    }

    //  �}�`��I������ړ�
    public int ShapeSelectMove()
    {
        //  �N�[�����Ԃ����炷
        if (coolTimer > 0.0f) coolTimer -= Time.deltaTime;

        //  ���͂��󂯎��
        Vector2 input = InputController();

        //  �e���͂ł̔ԍ��̕ύX(���E)
        if (input.x > DEAD_ZONE_ADD && selectShapeNum % 2 != 1 && coolTimer <= 0.0f)
        {
            selectShapeNum++;
            coolTimer = coolTime;
        }
        else if (input.x < -DEAD_ZONE_ADD && selectShapeNum % 2 != 0 && coolTimer <= 0.0f)
        {
            selectShapeNum--;
            coolTimer = coolTime;
        }
        //  �e���͂ł̔ԍ��̕ύX(�㉺)
        else if (input.y < -DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum += 2;
            if (selectShapeNum >= addShapeUIs.Count) selectShapeNum -= 2;
            coolTimer = coolTime;
        }
        else if (input.y > DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum -= 2;
            if (selectShapeNum < 0) selectShapeNum += 2;
            coolTimer = coolTime;
        }

        if (selectShapeNum > addShapeUIs.Count - 1) selectShapeNum = addShapeUIs.Count - 1;

        //  UI�̈ʒu��ς���
        gameObject.transform.position = addShapeUIs[selectShapeNum].transform.position;

        return selectShapeNum;
    }
    public int SelectData()
    {
        //  �N�[�����Ԃ����炷
        if (coolTimer > 0.0f) coolTimer -= Time.deltaTime;

        //  ���͂��󂯎��
        Vector2 input = InputController();

        //  �e���͂ł̔ԍ��̕ύX(���E)
        if (input.x > DEAD_ZONE_ADD && selectShapeNum % 3 != 2 && coolTimer <= 0.0f)
        {
            selectShapeNum++;
            coolTimer = coolTime;
        }
        else if (input.x < -DEAD_ZONE_ADD && selectShapeNum % 3 != 0 && coolTimer <= 0.0f)
        {
            selectShapeNum--;
            coolTimer = coolTime;
        }
        //  �e���͂ł̔ԍ��̕ύX(�㉺)
        else if (input.y < -DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum += 3;
            if (selectShapeNum >= addShapeUIs.Count) selectShapeNum -= 3;
            coolTimer = coolTime;
        }
        else if (input.y > DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum -= 3;
            if (selectShapeNum < 0) selectShapeNum += 3;
            coolTimer = coolTime;
        }

        if (selectShapeNum > addShapeUIs.Count - 1) selectShapeNum = addShapeUIs.Count - 1;

        //  UI�̈ʒu��ς���
        gameObject.transform.position = addShapeUIs[selectShapeNum].transform.position;

        return selectShapeNum;
    }

    public Vector2 InputController()
    {
        //  �Q�[���p�b�h����Ɏ擾����
        gamepad = Gamepad.current;
        if (gamepad == null) return Vector2.zero;

        Vector2 input = gamepad.leftStick.ReadValue();

        //  ���͂������������疳��(�f�b�h�]�[��)
        if (Mathf.Abs(input.x) < DEAD_ZONE && Mathf.Abs(input.y) < DEAD_ZONE) return Vector2.zero;

        return input;
    }
}
