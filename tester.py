import subprocess
import time

# Test cases según lo que pediste:
# args list, should_finish, expect_death, should_error
test_cases = [
    (["1",   "800", "200", "200"],      True,  True,  False),  # a philo should die
    (["3",   "310", "103", "103"],      False,  False, False),  # no one should die (preciso)
    (["4",   "310", "200", "100"],      True,  True,  False),  # a philo should die
    (["4",   "200", "205", "200"],      True,  True,  False),  # a philo should die
    (["5",   "800", "200", "200", "7"],True,  False, False),  # no one should die, stops after 7 eats
    (["4",   "410", "200", "200", "10"],True, False, False),  # no one should die, stops after 10 eats
    (["5",   "600", "200", "200"],      False, False, True),   # should error and not run
    (["4",   "-5",  "200", "200"],      False, False, True),   # error (negativo)
    (["4",   "600", "-5",  "200"],      False, False, True),   # error (negativo)
    (["4",   "600", "200", "-5"],       False, False, True),   # error (negativo)
    (["4",   "600", "200", "200", "-5"],False, False, True),   # error (negativo)
    (["5",   "800", "200", "200"],      False, False, False),  # no one should die (sin límite)
    (["5",   "600", "150", "150"],      False, False, False),  # no one should die (sin límite)
    (["4",   "410", "200", "200"],      False, False, False),  # no one should die (sin límite)
    (["100", "800", "200", "200"],      False, False, False),  # no one should die (sin límite)
    (["105", "800", "200", "200"],      False, False, False),  # no one should die (sin límite)
    (["200", "800", "200", "200"],      False, False, False),  # no one should die (sin límite)
]

def run_test(args, should_finish, expect_death, should_error, index):
    print(f"🔹 Test #{index + 1}: ./philo {' '.join(args)}")
    try:
        result = subprocess.run(
            ["./philo"] + args,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout = max(10, int(args[1]) // 10)
        )
        output = result.stdout.decode()
        error = result.stderr.decode()

        # Caso error esperado
        if should_error == True:
            if result.returncode != 0:
                print("✅ PASÓ (error esperado, programa no ejecutó correctamente)")
                return True
            else:
                print("❌ FALLO: se esperaba error, pero programa terminó bien")
                return False

        # Caso muerte esperada
        if expect_death == True:
            if "is dead" in output:
                print("✅ PASÓ (filósofo murió como se esperaba)")
                return True
            else:
                print("❌ FALLO: se esperaba muerte pero no ocurrió")
                return False

        # Caso que debe terminar correctamente sin muertes
        if not should_finish:
            if "is dead" in output:
                print("❌ FALLO: murió alguien cuando no debía")
                return False
            elif result.returncode == 0:
                print("⚠️ ADVERTENCIA: el programa terminó aunque no era necesario, pero sin errores.")
                return True  # o False si querés ser más estricto
            else:
                print("✅ PASÓ (timeout o salida inesperada permitida)")
                return True

        if not should_finish == True:
            if result.returncode == 0:
                print("❌ FALLO: programa terminó pero no debía")
                return False
            else:
                print("✅ PASÓ (timeout o final inesperado permitido)")
                return True

    except subprocess.TimeoutExpired:
        if should_finish:
            print("⏱️ TIMEOUT: debía terminar pero no lo hizo")
            return False
        else:
            print("✅ PASÓ (timeout esperado para ejecución prolongada sin errores)")
            return True
    except Exception as e:
        print(f"❌ EXCEPCIÓN inesperada: {e}")
        return False

def main():
    passed = 0
    failed = 0

    for i, (args, should_finish, expect_death, should_error) in enumerate(test_cases):
        if run_test(args, should_finish, expect_death, should_error, i):
            passed += 1
        else:
            failed += 1
        print("-" * 50)

    print("\n🎯 RESULTADO FINAL:")
    print(f"✔️ Pasaron: {passed}")
    print(f"❌ Fallaron: {failed}")

    if failed == 0:
        print("✅ ¡Tu proyecto pasa todas las pruebas!")
    else:
        print("⚠️ Algunas pruebas fallaron, revisa los detalles arriba.")

if __name__ == "__main__":
    main()
