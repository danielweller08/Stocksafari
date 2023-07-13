import { Component, OnInit } from '@angular/core';
import { DataService } from './shared/services/data.service';
import { Account } from './shared/models/account.model';
import { NavigationEnd, Router } from '@angular/router';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {
  
  isLoggedIn = false;
  account: Account | undefined = undefined;

  constructor(private _dataService: DataService, private _router: Router) { }

  ngOnInit(): void {
    // Subscribe to the login state.
    this._dataService._isLoggedIn.subscribe(value => this.isLoggedIn = value);

    // Subscribe to the account to display information in the top right corner.
    this._dataService._account.subscribe(value => this.account = value);

    // Subscribe to the error toastMessage.
    this._dataService._errorToastMessage.subscribe(value => {
      // Only show a toast if the value is not empty.
      if (value == "") {
        return;
      }

      // Set the message and show the toast.
      document.getElementById('error-toast-message')!.innerText = value;
      document.getElementById('error-toast')!.classList.add('d-block');

      // Set a timeout to hide the toast after 10 seconds.
      setTimeout(() => {
        document.getElementById('error-toast')!.classList.remove('d-block');
      }, 5000);
    });

    // Subscribe to the success toastMessage.
    this._dataService._successToastMessage.subscribe(value => {
      // Only show a toast if the value is not empty.
      if (value == "") {
        return;
      }

      // Set the message and show the toast.
      document.getElementById('success-toast-message')!.innerText = value;
      document.getElementById('success-toast')!.classList.add('d-block');

      // Set a timeout to hide the toast after 10 seconds.
      setTimeout(() => {
        document.getElementById('success-toast')!.classList.remove('d-block');
      }, 5000);
    });

    // Subscribe to the activated route.
    this._router.events.subscribe(
      value => {
        if (value instanceof NavigationEnd) {
          // Activate the correct tabs.
          if (value.url.startsWith("/stocks")) {
            document.getElementById('stocksTab')?.classList.add('active');
            document.getElementById('portfolioTab')?.classList.remove('active');
          }
          else if (value.url.startsWith("/portfolio")) {
            document.getElementById('stocksTab')?.classList.remove('active');
            document.getElementById('portfolioTab')?.classList.add('active');
          }
          else {
            document.getElementById('stocksTab')?.classList.remove('active');
            document.getElementById('portfolioTab')?.classList.remove('active');
          }
        }
      }
    );
  }

  login() {
    this.loginOrRegister('login');
  }

  register() {
    this.loginOrRegister('register');
  }

  loginOrRegister(method: string) {
    let succeeded = true;
    // Login or register using the API.
    this._dataService.loginOrRegister(method, (document.getElementById(`${method}InputUsername`) as any).value, (document.getElementById(`${method}InputPassword`) as any).value)
      .catch(e => {
        // An Error occured. Show an toast the relevant information.
        this._dataService._errorToastMessage.next(e);
        succeeded = false;
      })
      .finally(
        () => {
          if (succeeded === true){
            // Hide the modal.
            (document.getElementById(`${method}ModalDismiss`) as any).click();
          }
        }
      );
  }

  logout() {
    // Check if user is on portfolio page to redirect him.
    if (this._router.url.startsWith("/portfolio")) {
      this._router.navigateByUrl("/stocks");
    }

    this._dataService.logout();
  }

  closeErrorToast() {
    document.getElementById('error-toast')?.classList.remove('d-block');
  }

  closeSuccessToast() {
    document.getElementById('success-toast')?.classList.remove('d-block');
  }
}
