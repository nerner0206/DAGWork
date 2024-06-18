using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

//  ���C�N�V�[���̏��
public enum MakeSceneState
{
    Make,
    Preview,
    Save,
    Quit
};

//  ���C�N�̏��
public enum MState
{
    IconFree,
    AddShapeSelect,
    ShapeMove,
    Animation
};

public class CMakeManager : MonoBehaviour
{
    //  ���C�N�V�[���̏��
    public static MakeSceneState sceneState;
    //  ���C�N�̏��
    public static MState makeState;
    //  �Q�[���p�b�h
    private Gamepad gamepad;

    //  ���肷��
    private bool isMake;
    //  �Z�[�u�ԍ�
    private int saveNum;
    //  �A�j���[�V�����ԍ�
    private int animID;

    /// <summary>
    /// �I�u�W�F�N�g
    /// </summary>
    //  ������Icon
    [SerializeField] private GameObject moveIcon;
    //  �}�`��ǉ�����I�u�W�F�N�g
    [SerializeField] private GameObject shapeManager;
    //  �J����
    [SerializeField] private GameObject cam;
    //  �}�`�I�����X�g
    [SerializeField] private GameObject addShapeSelectList;
    //  �n���h��
    [SerializeField] private GameObject handle;
    //  �v���C���[
    [SerializeField] private GameObject player;
    [SerializeField] private GameObject hand;

    //  ������@UI
    [SerializeField] private List<GameObject> operater;
    //  �e�L�X�g
    [SerializeField] private List<Text> shapeNumTexts;

    //  �Z�[�uUI 
    [SerializeField] private GameObject saveUI;
    //  �A�C�R��
    [SerializeField] private GameObject moveIcon2;

    //  �p�����[�^�[
    [SerializeField] private GameObject paramater;
    //  �A�j���[�V����
    [SerializeField] private GameObject animator;

    /// <summary>
    /// �A�C�R���Ɣ�������I�u�W�F�N�g
    /// </summary>
    //  �}�`�̃��X�g��\��
    [SerializeField] private GameObject addArrowBack;
    //  �v���r���[�J�����摜
    [SerializeField] private GameObject previewCamImage;
    //  �A�j���[�V�����A�C�R��
    [SerializeField] private List<GameObject> animIcons;

    // Start is called before the first frame update
    private void Start()
    {
        //  ���C�N���
        sceneState = MakeSceneState.Make;
        //  �ŏ��̓t���[
        makeState = MState.IconFree;

        isMake = true;

        saveNum = 0;

        operater[0].SetActive(true);

        animID = 0;
    }
    // Update is called once per frame
    private void Update()
    {
        Debug.Log(animID);

        //  �Q�[���p�b�h���擾
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        switch(sceneState)
        {
            case MakeSceneState.Make:
                //  ���C�N��Ԃ̍X�V����
                MakeStateUpdate();
                //  �v���r���[�̃J�������n���h�����S�ɉ�]������
                gameObject.GetComponent<PreviewManager>().PreviewCamRot(handle.transform.position);
                //  y�������ꂽ�Ƃ�
                if (gamepad.buttonNorth.wasPressedThisFrame)
                {
                    //  �Z�[�u���邩�ǂ���
                    isSave();
                    return;
                }
                //  �����������v���r���[��Ԃɂ���
                if (gamepad.dpad.up.wasPressedThisFrame)
                {
                    ChangePreview();
                    return;
                }
                break;
            case MakeSceneState.Preview:
                //  �v���r���[�̍X�V����
                gameObject.GetComponent<PreviewManager>().PreviewUpdate();
                //  y�������ꂽ�Ƃ�
                if (gamepad.buttonNorth.wasPressedThisFrame)
                {
                    //  �Z�[�u���邩�ǂ���
                    isSave();
                    return;
                }
                //  ��Ea�{�^�����������烁�C�N��Ԃɂ���
                if (gamepad.dpad.up.wasPressedThisFrame || gamepad.aButton.wasPressedThisFrame)
                {
                    ChangeMake();
                    return;
                }
                break;
            case MakeSceneState.Save:
                saveNum = moveIcon2.GetComponent<MoveIcon>().SelectData();
                //  ����
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  �Z�[�u�f�[�^�P�ɃZ�[�u����
                    shapeManager.GetComponent<AddShapeManager>().Save(saveNum, animID);
                    //  �V�[���J��
                    SceneManager.LoadScene("SelectScene");
                }
                //  �߂�
                if (gamepad.buttonSouth.wasPressedThisFrame)
                {
                    if (isMake)
                    {
                        sceneState = MakeSceneState.Make;
                        moveIcon.SetActive(true);
                    }
                    else sceneState = MakeSceneState.Preview;

                    //  �J��
                    saveUI.GetComponent<DoMove>().DoTweenLocalMove(new Vector3(0.0f, 1280.0f, 0.0f));
                }
                    break;
            case MakeSceneState.Quit:
                break;
        }
    }
    //  ���C�N��Ԃ̍X�V
    private void MakeStateUpdate()
    {
        switch (makeState)
        {
            case MState.IconFree:
                //  �J�����̉�]
                cam.GetComponent<MakeCamera>().CamRot();
                //  �A�C�R���̈ړ�
                moveIcon.GetComponent<MoveIcon>().FreeMove();

                //  b�������ꂽ�Ƃ�
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  ���ꂼ���UI�Ŕ������Ă��邩
                    //  �}�`���X�g�{�^��
                    if (addArrowBack.GetComponent<UIHit>().hit) ChangeAddShapeSelect();
                    //  �v���r���[�J����
                    else if (previewCamImage.GetComponent<UIHit>().hit) ChangePreview();
                    //  ����ȊO�Ȃ�I�u�W�F�N�g�ɑ΂��ă��C���΂�
                    else
                    {
                        //  ���C���΂��ăI�u�W�F�N�g����������
                        bool isObj = shapeManager.GetComponent<EditShapeManager>().FlyingRay(
                            moveIcon.transform.position,
                            cam.transform.position);

                        //  �I�u�W�F�N�g��������Ώ������Ȃ�
                        if (!isObj) return;

                        //  �ҏW���[�h
                        makeState = MState.ShapeMove;
                        //  Icon���\���ɂ���
                        moveIcon.SetActive(false);
                        //  ������@��ς���
                        operater[2].SetActive(true);
                        operater[0].SetActive(false);
                        operater[1].SetActive(false);
                    }
                    return;
                }
                //  x�������ꂽ�Ƃ�
                if (gamepad.buttonWest.wasPressedThisFrame)
                {
                    //  �ǉ�����I�u�W�F�N�g��I��
                    ChangeAddShapeSelect();
                    return;
                }
                //  �A�j���[�V����
                if(gamepad.dpad.down.wasPressedThisFrame)
                {
                    //  �A�j���[�V������Ԃɂ���
                    makeState = MState.Animation;
                    //  UI�̕\��
                    paramater.SetActive(false);
                    animator.SetActive(true);
                    //  �v���C���[�̔�\��
                    player.SetActive(true);
                    //  �q�I�u�W�F�N�g�ɂ���
                    handle.transform.parent = hand.transform;
                    //  ����̈ʒu�E�p�x����
                    handle.transform.localPosition = new Vector3(-0.844f, 0.145f, -0.402f);
                    handle.transform.localEulerAngles = new Vector3(0.436f, -30.855f, 89.739f);
                    return;
                }
                //  a�������ꂽ�Ƃ�
                if (gamepad.buttonSouth.wasPressedThisFrame)
                {
                    //  �I�����邩�ǂ���
                    isQuit();
                    return;
                }

                break;
            case MState.AddShapeSelect:
                //  �J�����̉�]
                cam.GetComponent<MakeCamera>().CamRot();
                //  �A�C�R���̈ړ�
                int num = moveIcon.GetComponent<MoveIcon>().ShapeSelectMove();

                //  b�{�^���������ꂽ�Ƃ�
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  ��������
                    GameObject createObj = shapeManager.GetComponent<AddShapeManager>().AddShape(num);
                    //  ���₷
                    int sub = int.Parse(shapeNumTexts[num].text);
                    shapeNumTexts[num].text = (sub + 1).ToString();
                    //  �I���I�u�W�F�N�g��n��
                    shapeManager.GetComponent<EditShapeManager>().SetSelectObject(createObj);
                    //  ���X�g����ăI�u�W�F�N�g�ړ���Ԃɂ���
                    CloseList(MState.ShapeMove);
                    //  Icon���\���ɂ���
                    moveIcon.SetActive(false);
                    //  ������@��ς���
                    operater[2].SetActive(true);
                    operater[0].SetActive(false);
                    operater[1].SetActive(false);
                    return;
                }
                //  x��b�������ꂽ�Ƃ�
                if (gamepad.buttonWest.wasPressedThisFrame || gamepad.aButton.wasPressedThisFrame)
                {
                    //  ���X�g����ăt���[��Ԃɂ���
                    CloseList(MState.IconFree);
                    //  �A�C�R���̈ʒu��^�񒆂ɂ���
                    moveIcon.transform.localPosition = Vector3.zero;
                    //  ������@��ς���
                    operater[0].SetActive(true);
                    operater[2].SetActive(false);
                    operater[1].SetActive(false);
                    return;
                }

                break;
            case MState.ShapeMove:
                //  �J�����̉�]
                cam.GetComponent<MakeCamera>().CamRot();
                //  �ҏW����
                shapeManager.GetComponent<EditShapeManager>().EditShapeUpdate();
                //  ���[�^�[�̍X�V
                shapeManager.GetComponent<ParamaterManager>().MaterUpdate();

                //  x�������ꂽ�Ƃ�(�ǉ��Ń��X�g���J��)
                if (gamepad.buttonWest.wasPressedThisFrame)
                {
                    //  �I�u�W�F�N�g����������
                    shapeManager.GetComponent<EditShapeManager>().ResetSelectObject();
                    //  Icon��\���ɂ���
                    moveIcon.SetActive(true);
                    //  �ǉ�����I�u�W�F�N�g��I��
                    ChangeAddShapeSelect();
                    return;
                }
                //  b�������ꂽ�Ƃ�(����)
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  �I�u�W�F�N�g����������
                    shapeManager.GetComponent<EditShapeManager>().ResetSelectObject();
                    //  Icon��\���ɂ���
                    moveIcon.SetActive(true);
                    //  �A�C�R���̈ʒu�𒲐�
                    IconOnObject();
                    //  �A�C�R���t���[�ɂ���
                    makeState = MState.IconFree;
                    //  ������@��ς���
                    operater[0].SetActive(true);
                    operater[1].SetActive(false);
                    operater[2].SetActive(false);
                    return;
                }
                //  a�������ꂽ�Ƃ��i�폜�j
                if (gamepad.buttonSouth.wasPressedThisFrame)
                {
                    //  ���[�^�[�̍X�V
                    shapeManager.GetComponent<ParamaterManager>().DeleteMater();
                    //  �I�u�W�F�N�g���폜����
                    shapeManager.GetComponent<EditShapeManager>().DeleteShape();
                    //  Icon��\���ɂ���
                    moveIcon.SetActive(true);
                    //  �A�C�R���̈ʒu�𒲐�
                    IconOnObject();
                    //  �A�C�R���t���[�ɂ���
                    makeState = MState.IconFree;
                    //  ������@��ς���
                    operater[0].SetActive(true);
                    operater[1].SetActive(false);
                    operater[2].SetActive(false);
                    return;
                }

                break;
            case MState.Animation:
                //  �J�����̉�]
                cam.GetComponent<MakeCamera>().CamRot();
                //  �A�C�R���̈ړ�
                moveIcon.GetComponent<MoveIcon>().FreeMove();

                //  b�������ꂽ�Ƃ�
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  ���ꂼ���UI�Ŕ������Ă��邩
                    //  �}�`���X�g�{�^��
                    if (addArrowBack.GetComponent<UIHit>().hit)
                    {
                        //  UI�̕\��
                        paramater.SetActive(true);
                        animator.SetActive(false);
                        //  �q�I�u�W�F�N�g���O��
                        handle.transform.parent = null;
                        //  ������
                        handle.transform.position = Vector3.zero;
                        handle.transform.eulerAngles = Vector3.zero;
                        //  �v���C���[�̔�\��
                        player.SetActive(false);
                        //  �ύX
                        ChangeAddShapeSelect();
                    }
                    //  �v���r���[�J����
                    else if (previewCamImage.GetComponent<UIHit>().hit) ChangePreview();
                    //  �A�j���[�V�����A�C�R��
                    else if (animIcons[0].GetComponent<UIHit>().hit) ChangeAnim(0);
                    else if (animIcons[1].GetComponent<UIHit>().hit) ChangeAnim(1);
                    else if (animIcons[2].GetComponent<UIHit>().hit) ChangeAnim(2);
                    else if (animIcons[3].GetComponent<UIHit>().hit) ChangeAnim(3);
                    else if (animIcons[4].GetComponent<UIHit>().hit) ChangeAnim(4);
                    else if (animIcons[5].GetComponent<UIHit>().hit) ChangeAnim(5);
                    //  ����ȊO�Ȃ�I�u�W�F�N�g�ɑ΂��ă��C���΂�
                    else
                    {
                        //  ���C���΂��ăI�u�W�F�N�g����������
                        bool isObj = shapeManager.GetComponent<EditShapeManager>().FlyingRay(
                            moveIcon.transform.position,
                            cam.transform.position);

                        //  �I�u�W�F�N�g��������Ώ������Ȃ�
                        if (!isObj) return;

                        //  UI�̕\��
                        paramater.SetActive(true);
                        animator.SetActive(false);
                        //  �q�I�u�W�F�N�g���O��
                        handle.transform.parent = null;
                        //  ������
                        handle.transform.position = Vector3.zero;
                        handle.transform.eulerAngles = Vector3.zero;
                        //  �v���C���[�̔�\��
                        player.SetActive(false);
                        //  �ҏW���[�h
                        makeState = MState.ShapeMove;
                        //  Icon���\���ɂ���
                        moveIcon.SetActive(false);
                        //  ������@��ς���
                        operater[2].SetActive(true);
                        operater[0].SetActive(false);
                        operater[1].SetActive(false);
                    }
                    return;
                }
                //  �A�j���[�V����
                if (gamepad.dpad.down.wasPressedThisFrame)
                {
                    //  �A�j���[�V������Ԃɂ���
                    makeState = MState.IconFree;
                    //  UI�̕\��
                    paramater.SetActive(true);
                    animator.SetActive(false);
                    //  �q�I�u�W�F�N�g���O��
                    handle.transform.parent = null;
                    //  ������
                    handle.transform.position = Vector3.zero;
                    handle.transform.eulerAngles = Vector3.zero;
                    //  �v���C���[�̔�\��
                    player.SetActive(false);
                    return;
                }
                break;
        }
    }
    private void ChangeAnim(int num)
    {
        animID = num;
        gameObject.GetComponent<AnimatorManager>().SetAnimClip(animID);
        player.GetComponent<Animator>().SetTrigger("Attack");
    }
    //  �A�C�R���̈ʒu���I�u�W�F�N�g�̈ʒu�ɏo��
    public void IconOnObject()
    {
        //  �ʒu�����炤
        Vector3 objScreenPos = shapeManager.GetComponent<EditShapeManager>().GetObjScreenPos();
        //  �ʒu���A�C�R���ɓn��
        moveIcon.transform.position = new Vector3(objScreenPos.x, objScreenPos.y, 0.0f);
    }
    //  �؂�ւ�
    private void ChangeAddShapeSelect()
    {
        //  ��Ԃ�؂�ւ���
        makeState = MState.AddShapeSelect;
        //  ������@��ς���
        operater[1].SetActive(true);
        operater[0].SetActive(false);
        operater[2].SetActive(false);
        //  ���X�g���o��
        addShapeSelectList.GetComponent<DoMove>().DoTweenWorldMove(new Vector3(
            150.0f,
            addShapeSelectList.transform.position.y, 
            addShapeSelectList.transform.position.z));
    }
    //  ���X�g�����
    private void CloseList(MState makeSceneState)
    {
        //  ��Ԃ�؂�ւ���
        makeState = makeSceneState;
        //  ���X�g�����܂�
        addShapeSelectList.GetComponent<DoMove>().DoTweenWorldMove(new Vector3(
            -140.0f,
            addShapeSelectList.transform.position.y,
            addShapeSelectList.transform.position.z));
    }
    //  ��߂�
    private void isQuit()
    {
        sceneState = MakeSceneState.Quit;
    }
    //  �Z�[�u����
    private void isSave()
    {
        //  �Z�[�u��Ԃɂ���
        sceneState = MakeSceneState.Save;
        //  �A�C�R�����\��
        moveIcon.SetActive(false);
        //  �J��
        saveUI.GetComponent<DoMove>().DoTweenLocalMove(Vector3.zero);
    }
    //  �v���C���[��ON�ɂ���
    private void OnPlayer()
    {
        //  �v���C���[��\��
        player.SetActive(true);
    }
    //  �v���C���[��OFF�ɂ���
    private void OffPlayer()
    {
        //  �v���C���[���\��
        player.SetActive(false);
    }
    //  �v���r���[��Ԃɂ���
    private void ChangePreview()
    {
        //  �v���r���[��Ԃɂ���
        sceneState = MakeSceneState.Preview;
        //  �A�C�R�����\��
        moveIcon.SetActive(false);
        //  �v���r���[����
        isMake = false;
        //  �ό`
        gameObject.transform.GetComponent<PreviewManager>().MoveAfter();
    }
    //  ���C�N��Ԃɂ���
    private void ChangeMake()
    {
        //  ���C�N��Ԃɂ���
        sceneState = MakeSceneState.Make;
        //  �A�C�R����\��
        moveIcon.SetActive(true);
        //  ���C�N����
        isMake = true;
        //  �ό`
        gameObject.transform.GetComponent<PreviewManager>().MoveBefore();
    }
}