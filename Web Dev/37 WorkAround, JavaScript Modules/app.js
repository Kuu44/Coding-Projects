import {Print, getCadre, calculateTax, calculateBonus,getBenefits, reimbursementEligibility} from './employee.js';
import Employee from './employee.js';

function getEmployeeInformation(inputSalary) {
  Employee.salary = inputSalary;
  Print('Cadre: ' + getCadre());
  Print('Tax: ' + calculateTax());
  Print('Benefits: ' + getBenefits());
  Print('Bonus: ' + calculateBonus());
  Print('Reimbursement Eligibility: ' + reimbursementEligibility());
  Print(' *');
}

getEmployeeInformation(10000);
getEmployeeInformation(50000);
getEmployeeInformation(100000);
