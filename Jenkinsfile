pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout([$class: 'GitSCM', branches: [[name: '*/main']], extensions: [], userRemoteConfigs: [[url: 'https://github.com/plugosh/Simulation_Program']]])
            }
        }
        stage('publish') {
            steps {
                sh 'echo my-artifact > artifact2.zip'
                sh "chmod a+x ./Publish.sh"
                sh './Publish.sh'
            }
        }
    }
}
      
