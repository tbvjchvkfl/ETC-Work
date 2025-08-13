using UnityEngine;
using UnityEngine.InputSystem;

public class CameraController : MonoBehaviour
{
    public bool bIsMenuButton { get; set; } = false;

    public delegate void MenuToggleDelegate();
    public event MenuToggleDelegate OnMenuToggle;

    bool bIsControlActive = false;
    bool bIsModifyMoveSpeed = false;
    bool bIsModifyLookSpeed = false;

    float moveSpeed = 100.0f;
    float lookSpeed = 0.3f;

    float yawAxisValue = 0.0f;
    float pitchAxisValue = 0.0f;

    Vector3 movementDirection = Vector3.zero;
    Vector2 lookDirection = Vector2.zero;
    Vector2 scrollDirection = Vector2.zero;

    void Update()
    {
        Control();
    }

    void Control()
    {
        if (bIsControlActive)
        {
            transform.Translate(movementDirection * moveSpeed * Time.deltaTime, Space.Self);

            Vector3 InputRotation = new Vector3(lookDirection.y, lookDirection.x, 0.0f);
            
            yawAxisValue += InputRotation.y * lookSpeed;
            pitchAxisValue -= InputRotation.x * lookSpeed;

            //pitchAxisValue = Mathf.Clamp(pitchAxisValue, -35.0f, 35.0f);

            Vector3 cameraRotateDirection = new Vector3(pitchAxisValue, yawAxisValue, 0.0f);

            transform.rotation = Quaternion.Euler(cameraRotateDirection);
        }
    }

    public void OnMove(InputValue inputValue)
    {
        if (bIsControlActive)
        {
            Vector3 inputDirection = inputValue.Get<Vector3>();
            movementDirection = new Vector3(inputDirection.x, inputDirection.y, inputDirection.z);
        }
    }

    public void OnLook(InputValue inputValue)
    {
        if (bIsControlActive)
        {
            lookDirection = inputValue.Get<Vector2>();
            lookDirection = new Vector2(lookDirection.x, lookDirection.y);
        }
    }

    public void OnSpeedControl(InputValue inputValue)
    {
        scrollDirection = inputValue.Get<Vector2>();
        if (bIsModifyMoveSpeed)
        {
            moveSpeed = Mathf.Clamp(moveSpeed + scrollDirection.y * 10.0f, 10.0f, 200.0f);
        }
        else if (bIsModifyLookSpeed)
        {
            lookSpeed = Mathf.Clamp(lookSpeed + scrollDirection.y * 0.1f, 0.1f, 1.0f);
        }
    }

    public void OnActiveControll(InputValue inputValue)
    {
        bIsControlActive = inputValue.isPressed;
    }

    public void OnActiveModifySpeed(InputValue inputValue)
    {
        bIsModifyMoveSpeed = inputValue.isPressed;
    }

    public void OnActiveModifyLookSpeed(InputValue inputValue)
    {
        bIsModifyLookSpeed = inputValue.isPressed;
    }

    public void OnMenuButton()
    {
        OnMenuToggle?.Invoke();
    }
}
