pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('NuGet Restore') {
            steps {
                // 1. Завантажуємо nuget.exe прямо з офіційного сайту
                powershell 'Invoke-WebRequest https://dist.nuget.org/win-x86-commandline/latest/nuget.exe -OutFile nuget.exe'
                
                // 2. Відновлюємо пакети для нашого рішення
                bat 'nuget.exe restore test_repos.sln'
            }
        }

        stage('Build') {
            steps {
                // Тепер просто збираємо проект (пакети вже відновлені попереднім кроком)
                bat "\"${tool 'VS_Build'}\" test_repos.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x64"
            }
        }

        stage('Test') {
            steps {
                // Запускаємо тести
                bat "x64\\Debug\\test_repos.exe --gtest_output=xml:test_report.xml"
            }
        }
    }

    post {
        always {
            // Публікуємо результати
            junit 'test_report.xml'
        }
    }
}