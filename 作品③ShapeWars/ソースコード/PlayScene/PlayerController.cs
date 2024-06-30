using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;
using DG.Tweening;

//  �v���C���[�̏��
public enum PlayerState
{
    Move,       //  �ړ����
    Attack,     //  �U�����
    Avoidance,  //  ������
    Dead,       //  ���S���
    Cool,       //  �ҋ@���
    LockOn,     //  �ǐՏ��

    OverID
}

public class PlayerController : MonoBehaviour
{
    //  �v���C���[���
    private PlayerState playerState;
    //  �A�j���[�^�[
    private Animator animator;

    //  ��]����ڕW
    private Quaternion targetRotation;

    //  ����I�u�W�F�N�g
    private GameObject weapon;
    //  ����̍U����
    private int weaponPower;

    //  �v���C���[�̍ő�̗�
    [SerializeField] private int MaxHP = 0;
    //  �v���C���[�̗̑�
    private int hp;

    //  HP��UI
    [SerializeField] private Image GreenGauge;
    [SerializeField] private Image RedGauge;
    private Tween redGaugeTween;

    private bool muteki;
    private float mutekiTimer;
    [SerializeField] private float mutekiTime;

    //  �G�t�F�N�g
    [SerializeField] private GameObject deadE;

    private bool dead;

    private Gamepad gamepad;

    //  ������
    public void PlayerInit()
    {
        //  �v���C���[��Ԃ��ړ���
        playerState = PlayerState.Move;

        //  �A�j���[�^�[�R���|�[�l���g���擾
        animator = gameObject.GetComponent<Animator>();

        //  �����������
        weapon = new GameObject();
        //  ����̍U���͂�������
        weaponPower = 0;

        //  �̗͂�����
        hp = MaxHP;

        //  ������
        targetRotation = transform.rotation;

        muteki = false;
        mutekiTimer = 0.0f;

        dead = false;
    }

    //  �X�V����
    public void PlayerUpdate()
    {
        //  �������Ȃ�����(���S�Ɏ��S)
        if (playerState == PlayerState.Dead) return;

        //  �̗͂��O�ȉ����܂�����ł��Ȃ�
        if(hp <= 0 && playerState != PlayerState.Dead)
        {
            //  ���S��Ԃ�
            playerState = PlayerState.Dead;
            //  ���S�A�j���[�V�����̍Đ�
            animator.SetTrigger("Dead");
            //  �G�t�F�N�g�𐶐�
            Instantiate(deadE, gameObject.transform.position, Quaternion.identity);
            return;
        }

        //  ���G��Ԃɂ���
        if(muteki)
        {
            //  ���G���Ԃ�����
            mutekiTimer -= Time.deltaTime;
            //  ���G������
            if (mutekiTimer <= 0.0f) muteki = false;
        }

        //  �Q�[���p�b�h���擾����
        gamepad = Gamepad.current;
        //  �Q�[���p�b�h���ڑ�����Ă��Ȃ��ꍇ�������Ȃ�
        if (gamepad == null) return;

        //  �e��Ԃ̍X�V
        switch (playerState)
        {
            //  �ړ�
            case PlayerState.Move:
                //  ���X�e�B�b�N�̓��͏����擾
                float LR = gamepad.leftStick.ReadValue().x;
                float TB = gamepad.leftStick.ReadValue().y;

                //  ���͂���������ړ�����
                if (Mathf.Abs(LR) > 0.1f || Mathf.Abs(TB) > 0.1f)
                {
                    //  �J�����̕������琳�ʃx�N�g�����v�Z
                    var horizontalRotation = Quaternion.AngleAxis(Camera.main.transform.eulerAngles.y, Vector3.up);
                    //  �ړ������̌v�Z
                    Vector3 velocity = horizontalRotation * new Vector3(LR, 0.0f, TB).normalized;
                    //  �ړ����x�̌v�Z
                    var speed = gamepad.leftTrigger.ReadValue() > 0.8f ? 1.0f : 0.5f;
                    //  ��]���x�̌v�Z
                    var rotationSpeed = 600 * Time.deltaTime;

                    //  �ړ��������\���ɑ傫���Ƃ���]�ʂ����߂�
                    if (velocity.magnitude > 0.5f) targetRotation = Quaternion.LookRotation(velocity, Vector3.up);
                    //  ���ۂɉ�]����
                    transform.rotation = Quaternion.RotateTowards(transform.rotation, targetRotation, rotationSpeed);
                    //  �ړ������ɃA�j���[�V�������Đ�
                    animator.SetFloat("Move", velocity.magnitude * speed, 0.1f, Time.deltaTime);
                }

                //  �U������
                if (gamepad.rightTrigger.ReadValue() > 0.7f)
                {
                    //  �U����Ԃ�
                    playerState = PlayerState.Attack;
                    //  �U���A�j���[�V�����̍Đ�
                    animator.SetTrigger("Attack");
                    return;
                }

                //  �������
                if(gamepad.buttonNorth.wasPressedThisFrame)
                {
                    //  �����Ԃ�
                    playerState = PlayerState.Avoidance;
                    //  ����A�j���[�V�����̍Đ�
                    animator.SetTrigger("Avoidance");
                    return;
                }

                //  ���b�N�I����Ԃɂ���
                if (gamepad.buttonWest.wasPressedThisFrame)
                {
                    //  ���b�N�I����Ԃ�
                    playerState = PlayerState.LockOn;
                    return;
                }

                break;
            //  �U��
            case PlayerState.Attack:

                break;
            //  ���
            case PlayerState.Avoidance:

                break;
            //  �ǐ�
            case PlayerState.LockOn:

                break;
            //  �ҋ@
            case PlayerState.Cool:

                break;
        }
    }

    //  ���S�A�j���[�V�����̏I��
    void Dead()
    {
        //  ���S�Ɏ��S������Ԃɂ���
        dead = true;
    }
    //  �����U��I�������U����Ԃ���������
    void AttackAnimFinish()
    {
        //  �N�[����Ԃɂ���
    }

    //  ����I�u�W�F�N�g���擾
    public void SetWeaponObject(GameObject weapon)
    {
        this.weapon = weapon;
    }
    //  �v���C���[��Ԃ�n��
    public PlayerState GetPlayerState()
    {
        return playerState;
    }
    //  �A�j���[�V�������x
    public void SetAnimSpeed(float ratio)
    {
        animator.SetFloat("AnimSpeed", Mathf.Lerp(1.2f, 0.8f, ratio));
    }
    //  �U���͂�ݒ�
    public void SetAttackPower(float ratio)
    {
        weaponPower = (int)Mathf.Lerp(100.0f, 300.0f, ratio);
    }
    //  �U���͂�n��
    public int GetAttackPower()
    {
        return weaponPower;
    }

    //  �U�����󂯂�
    public void Damaged(int damage)
    {
        //  UI�̕ύX
        GaugeReduction((float)damage);
        //  �_���[�W���󂯂�
        hp -= damage;

        //  ��_���A�j���[�V�����̍Đ�
        animator.SetTrigger("hit");

        //  �U������������ړ��ɕύX����
        if (playerState == PlayerState.Attack) playerState = PlayerState.Move;

        muteki = true;
        mutekiTimer = mutekiTime;
    }

    public bool Muteki()
    {
        return muteki;
    }

    private void GaugeReduction(float reducationValue, float time = 1f)
    {
        var valueFrom = (float)hp / (float)MaxHP;
        var valueTo = ((float)hp - reducationValue) / (float)MaxHP;

        // �΃Q�[�W����
        GreenGauge.fillAmount = valueTo;

        if (redGaugeTween != null)
        {
            redGaugeTween.Kill();
        }

        // �ԃQ�[�W����
        redGaugeTween = DOTween.To(
            () => valueFrom,
            x => {
                RedGauge.fillAmount = x;
            },
            valueTo,
            time
        );
    }
}
